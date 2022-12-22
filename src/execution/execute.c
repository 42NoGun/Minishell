/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:30:18 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/22 16:59:37 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include "minishell.h"

bool	is_pipe(char *cmd)
{
	if (ft_strcmp(cmd, "|") == 0)
		return (true);
	return (false);
}

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


bool	is_ordered_heredoc(char **file_path, char *sequence)
{
	DIR				*dirp;
	struct dirent	*dp;
	int				i;

	i = 0;
	dirp = opendir("/tmp/heredoc/");
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
			_dup2(std_in, 0);
			file_path = get_heredoc_file_path();
			fd = open(file_path, O_RDONLY);
			if (open_error(fd, parent) == true)
				return (false);
			_dup2(fd, 0);
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

static bool	redirect_append_outstream(char *file, bool parent)
{
	int	fd;

	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, 0666);
	if (open_error(fd, parent))
		return (true);
	_dup2(fd, 1);
	_close(fd);
	return (false);
}

static bool	redirect_outstream(char *file, bool parent)
{
	int	fd;

	fd = open(file, O_CREAT | O_TRUNC | O_WRONLY, 0666);
	if (open_error(fd, parent))
		return (true);
	_dup2(fd, 1);
	_close(fd);
	return (false);
}

static bool	redirect_instream(char *file, bool parent)
{
	int	fd;

	fd = open(file, O_RDONLY, 0666);
	if (open_error(fd, parent))
		return (true);
	_dup2(fd, 0);
	_close(fd);
	return (false);
}

bool	redirection(char **redirections, bool parent)
{
	int		i;
	bool	open_error;

	i = 0;
	open_error = false;
	while (redirections[i])
	{
		if (ft_strcmp(redirections[i], ">>") == 0)
			open_error = redirect_append_outstream(redirections[i + 1], parent);
		if (ft_strcmp(redirections[i], ">") == 0)
			open_error = redirect_outstream(redirections[i + 1], parent);
		if (ft_strcmp(redirections[i], "<") == 0)
			open_error = redirect_instream(redirections[i + 1], parent);
		if (open_error)
			return (false);
		i += 2;
	}
	return (true);
}

void	remove_bracket(char *command)
{
	ft_memmove(command, command + 1, ft_strlen(command));
	command[ft_strlen(command) - 1] = 0;
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

bool	do_logical_operator(t_node **cur_node, char *token,
	int *prev_pipe_in, pid_t pid)
{
	if (is_logical_and(token) || is_logical_or(token))
	{
		*prev_pipe_in = -1;
		waitpid(pid, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			*cur_node = NULL;
			return (true);
		}
		*cur_node = (*cur_node)->next;
		if (g_exit_status != 0 && is_logical_and(token))
			skip_node_to_logical_operator(cur_node);
		if (g_exit_status == 0 && is_logical_or(token))
			skip_node_to_logical_operator(cur_node);
		return (true);
	}
	return (false);
}

bool	do_pipe(t_node **cur_node, char *token)
{
	if (is_pipe(token))
	{
		*cur_node = (*cur_node)->next;
		return (true);
	}
	return (false);
}

bool	do_parent_builtin(t_node **cur_node, t_list *env_list,
	t_context *c, t_pipe *p)
{
	if (p->has_pipe == false && is_builtin(*c->command)
		&& p->prev_pipe_in == -1)
	{
		if (heredoc(c->redirections, p->std_in, true) == true
			&& redirection(c->redirections, true) == true)
		{
			do_builtin(c->command, env_list, true);
			_dup2(p->std_in, 0);
			_dup2(p->std_out, 1);
		}
		*cur_node = (*cur_node)->next;
		free_2d_str(c->command);
		free_2d_str(c->redirections);
		return (true);
	}
	return (false);
}

void	do_parent_process(t_node **cur_node, t_context *c,
	t_pipe *p, t_pid_utils *process)
{
	push_back(process->pid_list, make_node((void *)(long long)process->pid));
	if (p->prev_pipe_in != -1)
		_close(p->prev_pipe_in);
	if (p->has_pipe)
	{
		p->prev_pipe_in = p->fd_pipe[0];
		_close(p->fd_pipe[1]);
	}
	*cur_node = (*cur_node)->next;
	free_2d_str(c->command);
	free_2d_str(c->redirections);
}

bool	pipe_connect(t_node *cur_next_node, t_pipe *p)
{
	t_token	*token;

	if (cur_next_node == NULL)
		return (false);
	token = (t_token *)((t_field *)cur_next_node->content)->start_ptr->content;
	if (ft_strcmp(token->value, "|") != 0)
		return (false);
	_pipe(p->fd_pipe);
	return (true);
}

static void	wait_child_process(t_list *pid_list, int std_in, int std_out)
{
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

static void	init_execute_utils(t_pipe *pipe_utils, t_pid_utils *process)
{
	pipe_utils->prev_pipe_in = -1;
	pipe_utils->std_in = dup(0);
	pipe_utils->std_out = dup(1);
	process->pid_list = init_list();
}

void	execute(t_list *exec_list, t_list *env_list)
{
	t_node		*cur_node;
	t_context	context;
	t_pipe		pipe_utils;
	t_pid_utils	process;

	init_execute_utils(&pipe_utils, &process);
	cur_node = exec_list->head;
	while (cur_node)
	{
		if (do_pipe(&cur_node, get_value(cur_node)))
			continue ;
		if (do_logical_operator(&cur_node,
				get_value(cur_node), &(pipe_utils.prev_pipe_in), process.pid))
			continue ;
		pipe_utils.has_pipe = pipe_connect(cur_node->next, &pipe_utils);
		expand_field(get_field(cur_node), env_list, is_subshell(cur_node));
		refine_field(get_field(cur_node),
			&context.command, &context.redirections);
		if (do_parent_builtin(&cur_node, env_list, &context, &pipe_utils))
			continue ;
		process.pid = do_child_process(&context,
				env_list, is_subshell(cur_node), &pipe_utils);
		do_parent_process(&cur_node, &context, &pipe_utils, &process);
	}
	wait_child_process(process.pid_list, pipe_utils.std_in, pipe_utils.std_out);
}
