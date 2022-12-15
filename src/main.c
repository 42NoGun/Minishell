/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/15 16:26:554 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include "minishell.h"

int		ft_strlen_no_space(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			++len;
		++i;
	}
	return (len);
}

bool	has_subshell_error(t_field *field, int field_len)
{
	t_node	*cur_node;
	int		value_len;
	int		i;
	char	*value;
	int		loop_len;

	loop_len = field_len;
	cur_node = field->start_ptr;
	while (loop_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(' && ft_strlen_no_space(value) == 2) // (공백 있는 경우)
			return (true);
		if (value[0] == '(' && field_len != 1) // () 토큰이 붙었을 때
			return (true);
		cur_node = cur_node->next;
		--loop_len;
	}
	return (false);
}

bool	check_bracket_syntax_error(t_list *exec_list)
{
	t_node		*cur_exec_node;
	t_field		*field;

	cur_exec_node = exec_list->head;
	while (cur_exec_node)
	{
		field = (t_field *)cur_exec_node->content;
		if (has_subshell_error(field, field->len))
		{
			ft_putstr_fd("minishell : subshell syntax error\n", 2);
			g_exit_status = 2 << 8;
			return (false);
		}
		cur_exec_node = cur_exec_node->next;
	}
	return (true);
}

// // // (echo hello )
// bool	has_heredoc(t_field *field, int field_len, int i)
// {
// 	t_node	*cur_node;
// 	int		value_len;
// 	int		i;
// 	char	*value;
// 	int		loop_len;

// 	loop_len = field_len;
// 	cur_node = field->start_ptr;
// 	while (loop_len)
// 	{
// 		// 1. 서브쉘이면
// 		// value 자체를 끝가지 돌면서, << 있을 때 마다 열어준다.
// 		// 따옴표 있으면 밀어준다.
// 		// i로 파일 이름만들어주는 걸 어떻게 이걸 적용하죠?
// 		// value = ((t_token *)cur_node->content)->value;
// 		// if (value[0] == '(' && ft_strlen_no_space(value) == 2) // (공백 있는 경우)
// 		// 	return (true);
// 		// if (value[0] == '(' && field_len != 1) // () 토큰이 붙었을 때
// 		// 	return (true);
// 		// cur_node = cur_node->next;
// 		// --loop_len;
// 	}
// 	return (false);
// }

void	skip_quote_content(char **value, char quote)
{
	size_t	len;

	len = ft_strchr((*value + 1), quote) - *value;
	*value += len;
}

void	push_back_limiter(t_node *node, t_list *limiter_list)
{
	char	*value;

	value = ((t_token *)node->content)->value;
	push_back(limiter_list, make_node(ft_strdup(value)));
}

char	*get_limiter(char *value)
{
	int	end;

	end = 0;
	while (value[end])
	{
		if (!ft_isalnum(value[end]))
			break ;
		++end;
	}
	return (ft_substr(value, 0, end));
}

void	push_back_subshell_limiter(char *value, t_list *limiter_list)
{
	char	*limiter;

	++value;
	while (*value && *value == ' ')
		++value;
	limiter = get_limiter(value);
	push_back(limiter_list, make_node(limiter));
}

int	count_heredoc(t_field *field, int field_len, t_list *limiter_list)
{
	t_node	*cur_node;
	char	*value;
	int		loop_len;
	int		heredoc_count;

	heredoc_count = 0;
	cur_node = field->start_ptr;
	while (field_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(')
		{		
			while (*value)
			{
				if (*value == '"' || *value == '\'')
					skip_quote_content(&value, *value);
				else
				{
					if (*value == '<' && *(value + 1) == '<')
					{
						++heredoc_count;
						++value; // 커서가 두번째 <에 있어요
						push_back_subshell_limiter(value, limiter_list);
					}
				}
				++value;
			}
		}
		else
		{
			if (ft_strcmp(value, "<<") == 0)
			{
				++heredoc_count;
				push_back_limiter(cur_node->next, limiter_list);
			}
		}
		cur_node = cur_node->next;
		--field_len;
	}
	return (heredoc_count);
}

int check_heredoc(t_list *exec_list, t_list *limiter_list)
{
	t_node		*cur_exec_node;
	t_field		*field;
	int			heredoc_count;

	cur_exec_node = exec_list->head;
	heredoc_count = 0;
	while (cur_exec_node)
	{
		field = (t_field *)cur_exec_node->content;
		heredoc_count += count_heredoc(field, field->len, limiter_list);
		cur_exec_node = cur_exec_node->next;
	}
	return (heredoc_count);
}

void	write_heredoc(char *file_path, t_list *limiter_list)
{
	int		fd;
	int		i;
	char	*line;
	char	*limiter;


	limiter = (limiter_list->head->content);
	pop_front(limiter_list);
	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_terminate("write_heredoc, open");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

bool	make_heredoc_file(t_list *exec_list)
{
	int			count;
	int			i;
	int			fd;
	char		*current_file_sequence;
	char		*current_file_path;
	const char	*file_name_prefix = "/tmp/heredoc/";
	t_list		*limiter_list;

	i = 0;
	limiter_list = init_list();
	count = check_heredoc(exec_list, limiter_list);
	while (i < count)
	{
		current_file_sequence = ft_itoa(i);
		current_file_path = ft_strjoin_right_free(file_name_prefix, current_file_sequence);
		write_heredoc(current_file_path, limiter_list);
		++i;
	}
	return (true);
}

void	subshell_logic(int argc, char **argv, t_list *env_list)
{
	int	i;

	t_list *cmd_list;
	t_tree *cmd_tree;
	t_list *cmd_exec_list;
	char *line;

	cmd_list = init_list();
	cmd_tree = init_tree();
	line = ft_strdup(argv[1]);
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return ;
	}
	if (is_correct_pair(line) == false)
	{
		free(line);
		return ;
	}
	tokenize(line, cmd_list);
	parser(cmd_tree, cmd_list);
	if (check_syntax_error(cmd_tree) == false)
	{
		free(line);
		return ;
	}
	cmd_exec_list = convert_tree_to_exec_list(cmd_tree);
	if (check_bracket_syntax_error(cmd_exec_list) == false)
	{
		free(line);
		return ;
	}
	execute(cmd_exec_list, env_list);
	free(line);
}

void	signal_interrupt(int signum)
{
	g_exit_status = 130 << 8;
	ft_putchar_fd('\n', 2);
	if (rl_on_new_line() == -1)
		exit(1);
	rl_replace_line("", 10);
	rl_redisplay();
}

void	define_signal(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

void copy_envp(t_list *env_list, char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		push_back(env_list, make_node(ft_strdup(envp[i])));
		++i;
	}
}

char	*ft_getenv(t_list *env_list, char *env)
{
	t_node	*cur_node;
	int		env_len;

	cur_node = env_list->head;
	env_len = ft_strlen(env);
	while (cur_node)
	{
		if (env_len != 0 && ft_strncmp((char *)(cur_node->content), env, env_len) == 0)
		{
			return (ft_strchr((char *)cur_node->content, '=') + 1);
		}
		cur_node = cur_node->next;
	}
	return (NULL);
}

void	ft_setenv(t_list *env_list, char *key, char *command)
{
	t_node	*cur_node;

	cur_node = env_list->head;
	while (cur_node)
	{
		if (ft_strncmp((char *)(cur_node->content), key, ft_strlen(key)) == 0)
		{
			free(cur_node->content);
			cur_node->content = command;
			return ;
		}
		cur_node = cur_node->next;
	}
	return ;
}

int main(int argc, char **argv, char **envp, char **envp2)
{
	char *line;
	t_list *cmd_list;
	t_tree *cmd_tree;
	t_list *cmd_exec_list;
	t_list *env_list;

	int i = 0;
	errno = 0;
	env_list = init_list();
	copy_envp(env_list, envp);
	if (argc >= 2)
	{
		subshell_logic(argc, argv, env_list);
		return (WEXITSTATUS(g_exit_status));
	}
	while (1)
	{
		define_signal();
		cmd_list = init_list();
		cmd_tree = init_tree();
		line = readline("minishell > ");
		signal(SIGINT, SIG_IGN);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			exit(0);
		}
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		if (is_correct_pair(line) == false)
		{
			free(line);
			continue;
		}
		tokenize(line, cmd_list);
		parser(cmd_tree, cmd_list);
		if (check_syntax_error(cmd_tree) == false)
		{
			free(line);
			continue;
		}
		cmd_exec_list = convert_tree_to_exec_list(cmd_tree);
		if (check_bracket_syntax_error(cmd_exec_list) == false)
		{
			free(line);
			continue;
		}
		pid_t pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			make_heredoc_file(cmd_exec_list);
			return (WEXITSTATUS(g_exit_status));
		}
		waitpid(pid, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			if (g_exit_status == 3)
				write(2, "Quit: 3\n", 9);
			else if (g_exit_status == 2)
				write(2, "\n", 1);
			g_exit_status = (g_exit_status + 128) << 8;
			/*
			모든동적할당 메모리 해제할 것
			*/
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		execute(cmd_exec_list, env_list);
		free(line);
		/*
		모든동적할당 메모리 해제할 것
		*/
	}
	return (0);
}
