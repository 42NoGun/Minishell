/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/12 11:46:221 by cheseo           ###   ########.fr       */
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

	cur_node = env_list->head;
	while (cur_node)
	{
		if (ft_strncmp((char *)(cur_node->content), env, ft_strlen(env)) == 0)
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

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_list *cmd_list; // free필요
	t_tree *cmd_tree;
	t_list *cmd_exec_list;
	t_list *env_list;

	errno = 0;
	if (argc >= 2)
	{
		subshell_logic(argc, argv, env_list);
		return (WEXITSTATUS(g_exit_status));
	}
	env_list = init_list();
	copy_envp(env_list, envp);
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
		execute(cmd_exec_list, env_list);
		free(line);
	}
	return (0);
}
