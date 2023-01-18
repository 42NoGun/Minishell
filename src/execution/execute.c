/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:30:18 by hanbkim           #+#    #+#             */
/*   Updated: 2023/01/18 20:44:39 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include "minishell.h"

static void	skip_node_to_logical_operator(t_node **cur_node)
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

static bool	do_logical_operator(t_node **cur_node, char *token,
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

static void	do_parent_process(t_node **cur_node, t_context *c,
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

static void	wait_child_process(t_list *pid_list, int std_in, int std_out)
{
	while (pid_list->len)
	{
		waitpid((long long)pid_list->head->content, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			if (g_exit_status == 3)
			{
				_write(2, "Quit: 3\n", 9);
				g_exit_status = (g_exit_status + 128) << 8;
				break ;
			}
			else if (g_exit_status == 2)
			{
				_write(2, "\n", 1);
				g_exit_status = (g_exit_status + 128) << 8;
				break ;
			}
			g_exit_status = (g_exit_status + 128) << 8;
		}
		pop_front(pid_list);
	}
	free_list_only_node(pid_list);
	_close(std_in);
	_close(std_out);
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
