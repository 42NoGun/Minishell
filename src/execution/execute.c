/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:39:03 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/13 15:09:26 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "minishell.h"

bool is_logical_and(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0)
		return (true);
	return (false);
}

bool is_logical_or(char *cmd)
{
	if (ft_strcmp(cmd, "||") == 0)
		return (true);
	return (false);
}

void	skip_node_to_logical_operator(t_node **cur_node)
{
	t_field	*cur_field;
	t_token	*start_token;

	while (*cur_node)
	{	
		cur_field = (t_field *)((*cur_node)->content);
		start_token = (t_token *)(cur_field->start_ptr->content);
		if (is_logical_and(start_token->value)
			|| is_logical_or(start_token->value))
			break ;
		(*cur_node) = (*cur_node)->next;
	}
}

bool	is_builtin(char	*command)
{
	if (!command)
		return false;
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}

bool	pipe_connect(t_node *cur_next_node, int fd_pipe[2])
{
	t_token	*token;
	
	if (cur_next_node  == NULL)
		return (false);
	token = (t_token *) ((t_field *)cur_next_node->content)->start_ptr->content;
	if (ft_strcmp(token->value, "|") != 0)
		return (false);
	if (pipe(fd_pipe) == -1)
		ft_terminate("pipe_connect, pipe");
	return (true);
}

void	make_heredoc(char *limiter)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("/tmp/.here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_terminate("make_heredoc, open");
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
bool	heredoc(char **redirections, int std_in, bool parent)
{
	int i;
	int	fd;

	i = 0;
	while (redirections[i])
	{		
		if (ft_strcmp(redirections[i], "<<") == 0)
		{
			dup2(std_in, 0); // heredoc 여러개 들어왓을 때 처리하려고 vs pipe랑 heredoc왔을 때 파이프연결을 이게 끊어비림
 			make_heredoc(redirections[i + 1]);
			fd = open("/tmp/.here_doc", O_RDONLY);
			if (fd == -1 && !parent)
				ft_terminate("redirection, open");
			if (fd == -1 && parent)
			{
				ft_putendl_fd(strerror(errno), 2);
				return (false);
			}
			dup2(fd, 0);
			close(fd);
			unlink("/tmp/.here_doc");
		}
		i += 2; 
	}
	close(std_in);
	return (true);
}

bool	redirection(char **redirections, int std_in, bool parent)
{
	int i;
	int	fd;

	i = 0;
	while (redirections[i])
	{		
		if (ft_strcmp(redirections[i], ">>") == 0)
		{
			fd = open(redirections[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (fd == -1)
				ft_terminate("redirection, open");	
			dup2(fd, 1);
			close(fd);
		}
		else if (ft_strcmp(redirections[i], "<") == 0)
		{
			fd = open(redirections[i + 1], O_RDONLY);
			if (fd == -1 && !parent)
				ft_terminate("redirection, open");
			if (fd == -1 && parent)
			{
				ft_putendl_fd(strerror(errno), 2);
				return (false);
			}
			dup2(fd, 0);
			close(fd);
		}
		else if (ft_strcmp(redirections[i], ">") == 0)
		{
			fd = open(redirections[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0666);
			if (fd == -1 && !parent)
				ft_terminate("redirection, open");
			if (fd == -1 && parent)
			{
				ft_putendl_fd(strerror(errno), 2);
				return (false);
			}
			dup2(fd, 1);
			close(fd);
		}
		i += 2; 
	}
	close(std_in);
	return (true);
}

void	remove_bracket(char *command)
{
	ft_memmove(command, command + 1, ft_strlen(command));
	command[ft_strlen(command) - 1] = 0;
} 

char	**put_program_name(char **old_command)
{
	char **new_command;
	int	i;

	i = 0;
	while(old_command[i])
		++i;
	new_command = ft_calloc(sizeof(char *), i + 2);
	new_command[0] = ft_strdup("./minishell");
	i = 1;
	while(old_command[i - 1])
	{
		new_command[i] = ft_strdup(old_command[i - 1]);
		++i;
	}
	i = 0;
	while (old_command[i])
	{
		free(old_command[i]);
		++i;
	}
	free(old_command);
	return (new_command);
}

bool	is_subshell(char **command)
{
	if (command[0][0] != '(')
		return (false);

	return (true);
}


void	do_builtin(char **command, t_list *env_list)
{
	if (ft_strcmp(*command, "echo") == 0)
	{
		b_echo(command);
	}
	if (ft_strcmp(*command, "cd") == 0)
	{
		b_cd(command, env_list);
	}
	if (ft_strcmp(*command, "pwd") == 0)
	{
		b_pwd();
	}
	if (ft_strcmp(*command, "export") == 0)
	{
		b_export(command, env_list);
	}
	// if (ft_strcmp(*command, "unset") == 0)
	// {
	// }
	if (ft_strcmp(*command, "env") == 0)
	{
		b_env(command, env_list);
	}
	if (ft_strcmp(*command, "exit") == 0)
	{
		b_exit(command);
	}
}

void	find_path(char **command, t_list *env_list)
{
	char		**path_list;
	int			i;
	char		*command_with_path;
	struct stat	buf;

	if (ft_strchr(*command, '/') != NULL)
	{
		if (lstat(*command, &buf) != 0)
			*command = NULL;
		return ;
	}
	path_list = ft_split(ft_getenv(env_list, "PATH"), ':');
	i = 0;
	while (path_list[i])
	{
		command_with_path = ft_strjoin_left_free(path_list[i], "/");
		command_with_path = ft_strjoin_left_free(command_with_path, *command);
		if (lstat(command_with_path, &buf) == 0)
		{
			free(*command);
			*command = command_with_path;
			return ;
		}
		++i;
	}
	*command = NULL;
}

char	**list_to_2d_array(t_list *envp_list)
{
	char	**arr;
	int		i;
	t_node	*cur_node;

	arr = ft_calloc(sizeof(char *), envp_list->len + 1);
	i = 0;
	cur_node = envp_list->head;
	while (cur_node)
	{
		arr[i] = (char *) cur_node->content;
		++i;
		cur_node = cur_node->next;
	}
	return (arr);
}

void execute(t_list *exec_list, t_list *env_list)
{
	t_field	*field;
	t_token	*token;
	t_node	*cur_node;
	t_node	*cur_next_node;
	char	**command;
	char	**redirections;
	int		fd_pipe[2];
	int 	prev_pipe_in;
	bool	has_pipe;
	char	*path;
	t_list	*pid_list;
	pid_t	pid;
	int 	std_in;
	int		std_out;

	pid_list = init_list();
	prev_pipe_in = -1;
	cur_node = exec_list->head;
	std_in = dup(0);
	std_out = dup(1);
	// i = 0;
	while (cur_node)
	{
		cur_next_node = cur_node->next;
		field = (t_field *) cur_node->content;
		token = (t_token *)(field->start_ptr->content);
		if (ft_strcmp(token->value, "|") == 0)
		{
			cur_node = cur_node->next;
			continue ;
		}
		else if (is_logical_and(token->value))
		{	
			waitpid(pid, &g_exit_status, 0);
			if (WIFSIGNALED(g_exit_status) == true)
			{
				cur_node = NULL;
				continue;
			}
			if (g_exit_status == 0)
			{
				cur_node = cur_node->next;
				continue ;
			}
			else
			{
				cur_node = cur_next_node->next;
				skip_node_to_logical_operator(&cur_node);
				continue ;
			}
		}
		else if (is_logical_or(token->value))
		{
			waitpid(pid, &g_exit_status, 0);
			if (WIFSIGNALED(g_exit_status) == true)
			{
				cur_node = NULL;
				continue;
			}
			if (g_exit_status == 0)
			{
				cur_node = cur_node->next;
				skip_node_to_logical_operator(&cur_node);
				continue ;
			}
			else
			{
				cur_node = cur_node->next;
				continue ;
			}
		}	
		has_pipe = pipe_connect(cur_next_node, fd_pipe);
		expand_field(field, env_list);
		refine_field(field, &command, &redirections); // command_argv 인수추가
		if (has_pipe == false && is_builtin(*command) && prev_pipe_in == -1) 
		{
			if (heredoc(redirections, std_in, true) == true && redirection(redirections, std_in, true) == true)
			{
				do_builtin(command, env_list);
				dup2(std_in, 0);
				dup2(std_out, 1);
			}
			cur_node = cur_node->next;
			continue ;
		}
		pid = fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			if (prev_pipe_in != -1)
			{
				dup2(prev_pipe_in, 0);
				close(prev_pipe_in);
			}
			// heredoc
			heredoc(redirections, std_in, false);
			if (has_pipe)
			{
				dup2(fd_pipe[1], 1);
				close(fd_pipe[1]);
				close(fd_pipe[0]);
				redirection(redirections, std_in, false);
			}
			else
				redirection(redirections, std_in, false);
			if (*command == NULL) // ㅇㅣㄸ보기
				exit(0);
			if (is_subshell(command) == true)
			{
				remove_bracket(*command);
				command = put_program_name(command);
			}
			else if (is_builtin(*command) == true)
			{
				do_builtin(command, env_list);
				exit(0);
			}
			else
				find_path(command, env_list);
			// command 2ㅊ원 배열
			// 아닐때는 -> *
			if (execve(command[0], command, list_to_2d_array(env_list)) == -1)
			{
				write(2, "ㄴㅏ능능한한비킴ㅏ\n", 29);
				exit(127);
			}
		}
		push_back(pid_list, make_node((void *)(long long)pid));
		if (prev_pipe_in != -1)
			close(prev_pipe_in);
		if (has_pipe)
		{
			prev_pipe_in = fd_pipe[0];
			close(fd_pipe[1]);
		}
		// i++;
		cur_node = cur_node->next;
	}
	// 여기에서 전부기다리는 것
	while (pid_list->len)
	{
		//signal(SIGINT, SIG_IGN);
		waitpid((pid_t) pid_list->head->content, &g_exit_status, 0);
		printf("g_exit_status : %d\n", g_exit_status);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			if (g_exit_status == 3)
				write(2, "Quit: 3\n", 9);
			else if (g_exit_status == 2)
				write(2, "\n", 1);
			g_exit_status = (g_exit_status + 128) << 8 ;
		}
		pop_front(pid_list);
	}
	close(std_in);
	close(std_out);
}