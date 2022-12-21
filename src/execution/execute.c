/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjeseo <cjiyunpeseo@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:30:18 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/21 10:42:20 by cjiyunpeseo          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "minishell.h"

bool	is_logical_and(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0)
		return (true);
	return (false);
}

bool	is_logical_or(char *cmd)
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
		return (false);
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

	if (cur_next_node == NULL)
		return (false);
	token = (t_token *)((t_field *)cur_next_node->content)->start_ptr->content;
	if (ft_strcmp(token->value, "|") != 0)
		return (false);
	_pipe(&fd_pipe);
	return (true);
}

bool	is_ordered_heredoc(char **file_path, char *sequence)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	i = 0;
	dirp = opendir("/tmp/heredoc/"); // error 처리 필요 
	dp = readdir(dirp);
	dp = readdir(dirp);
	while (true)
	{
		dp = readdir(dirp);
		if (dp == NULL)
		{
			closedir(dirp);
			return (false);
		}
		if (ft_strcmp(sequence, dp->d_name) == 0)
		{
			*file_path = ft_strdup(dp->d_name);
			closedir(dirp);
			return (true);
		}
	}
}

char	*get_heredoc_file_path(void)
{
	char			*file_path;
	char			*sequence;
	const char		*prefix = "/tmp/heredoc/";
	int				i;

	i = 0;
	while (1)
	{
		sequence = ft_itoa(i);
		if (is_ordered_heredoc(&file_path, sequence))
		{
			free(sequence);
			break ;
		}
		free(sequence);
		++i;
	}
	file_path = ft_strjoin_right_free(prefix, file_path);
	return (file_path);
}

bool	open_error(int fd, bool parent)
{
	if (fd == -1 && !parent)
		ft_terminate("redirection, open");
	if (fd == -1 && parent)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (true);
	}
	return (false);
}

bool	heredoc(char **redirections, int std_in, bool parent)
{
	int		i;
	int		fd;
	char	*file_path;

	i = 0;
	while (redirections[i])
	{	
		if (ft_strcmp(redirections[i], "<<") == 0)
		{
			dup2(std_in, 0);
			file_path = get_heredoc_file_path();
			fd = open(file_path, O_RDONLY);
			if (open_error(fd, parent) == true)
				return (false);
			dup2(fd, 0);
			_close(fd);
			unlink(file_path);
			free(file_path);
		}
		i += 2;
	}
	if (!parent)
		_close(std_in);
	return (true);
}

bool	redirection(char **redirections, bool parent)
{
	int	i;
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
			_close(fd);
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
			_close(fd);
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
			_close(fd);
		}
		i += 2;
	}
	return (true);
}

void	remove_bracket(char *command)
{
	ft_memmove(command, command + 1, ft_strlen(command));
	command[ft_strlen(command) - 1] = 0;
}

char	**put_program_name(char **old_command)
{
	char	**new_command;
	int		i;

	i = 0;
	while (old_command[i])
		++i;
	new_command = ft_calloc(sizeof(char *), i + 2);
	new_command[0] = ft_strdup("./minishell");
	i = 1;
	while (old_command[i - 1])
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

void	do_builtin(char **command, t_list *env_list, bool parent)
{
	if (ft_strcmp(*command, "echo") == 0)
		g_exit_status = b_echo(command) << 8 ;
	else if (ft_strcmp(*command, "cd") == 0)
		g_exit_status = b_cd(command, env_list) << 8;
	else if (ft_strcmp(*command, "pwd") == 0)
		g_exit_status = b_pwd() << 8;
	else if (ft_strcmp(*command, "export") == 0)
		g_exit_status = b_export(command, env_list) << 8;
	else if (ft_strcmp(*command, "unset") == 0)
		g_exit_status = b_unset(command, env_list) << 8;
	else if (ft_strcmp(*command, "env") == 0)
		g_exit_status = b_env(command, env_list) << 8;
	else if (ft_strcmp(*command, "exit") == 0)
		g_exit_status = b_exit(command, parent) << 8;
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

void	expand_field(t_field *field, t_list *env_list, bool is_subshell)
{
	int		len;
	t_token	*cur_token;
	t_node	*cur_node;

	len = field->len;
	cur_node = field->start_ptr;
	if (is_subshell)
		return ;
	while (len)
	{
		cur_token = (t_token *)cur_node->content;
		expand_dollar(cur_token, env_list);
		expand_wildcard(cur_token);
		cur_node = cur_node->next;
		--len;
	}
}

void	execute(t_list *exec_list, t_list *env_list)
{
	t_field	*field;
	t_token	*token;
	t_node	*cur_node;
	t_node	*cur_next_node;
	char	**command;
	char	**redirections;
	int		fd_pipe[2];
	int		prev_pipe_in;
	bool	has_pipe;
	t_list	*pid_list;
	pid_t	pid;
	int		std_in;
	int		std_out;
	bool	is_subshell;

	pid_list = init_list();
	prev_pipe_in = -1;
	cur_node = exec_list->head;
	std_in = dup(0);
	std_out = dup(1);
	while (cur_node)
	{
		is_subshell = false;
		cur_next_node = cur_node->next;
		field = (t_field *) cur_node->content;
		token = (t_token *)(field->start_ptr->content);
		if (token->value[0] == '(')
			is_subshell = true;
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
				continue ;
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
				continue ;
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
		expand_field(field, env_list, is_subshell);
		refine_field(field, &command, &redirections, 0);
		if (has_pipe == false && is_builtin(*command) && prev_pipe_in == -1)
		{
			if (heredoc(redirections, std_in, true) == true
				&& redirection(redirections, true) == true)
			{
				do_builtin(command, env_list, true);
				dup2(std_in, 0);
				dup2(std_out, 1);
			}
			cur_node = cur_node->next;
			free_2d_str(command);
			free_2d_str(redirections);
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
				_close(prev_pipe_in);
			}
			heredoc(redirections, std_in, false);
			if (has_pipe)
			{
				dup2(fd_pipe[1], 1);
				_close(fd_pipe[1]);
				_close(fd_pipe[0]);
				redirection(redirections, false);
			}
			else
				redirection(redirections, false);
			if (*command == NULL)
				exit(0);
			if (is_subshell)
			{
				remove_bracket(*command);
				command = put_program_name(command);
			}
			else if (is_builtin(*command) == true)
			{
				do_builtin(command, env_list, false);
				exit(0);
			}
			else
				find_path(command, env_list);
			if (execve(command[0], command, list_to_2d_array(env_list)) == -1)
			{
				_write(2, "command not found\n", 19);
				exit(127);
			}
		}
		push_back(pid_list, make_node((void *)(long long)pid));
		if (prev_pipe_in != -1)
			_close(prev_pipe_in);
		if (has_pipe)
		{
			prev_pipe_in = fd_pipe[0];
			_close(fd_pipe[1]);
		}
		cur_node = cur_node->next;
		free_2d_str(command);
		free_2d_str(redirections);
	}
	while (pid_list->len)
	{
		waitpid((pid_t) pid_list->head->content, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			if (g_exit_status == 3)
				_write(2, "Quit: 3\n", 9);
			else if (g_exit_status == 2)
			{
				_write(2, "\n", 1);
				g_exit_status = (g_exit_status + 128) << 8 ;
				break ;
			}
			g_exit_status = (g_exit_status + 128) << 8 ;
		}
		pop_front(pid_list);
	}
	free_list_only_node(pid_list);
	_close(std_in);
	_close(std_out);
}
