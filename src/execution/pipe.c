/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:30:18 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/23 11:26:42 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_execute_utils(t_pipe *pipe_utils, t_pid_utils *process)
{
	pipe_utils->prev_pipe_in = -1;
	pipe_utils->std_in = dup(0);
	pipe_utils->std_out = dup(1);
	process->pid_list = init_list();
}

void	set_child_pipe(t_pipe *p, t_context *c)
{
	if (p->prev_pipe_in != -1)
	{
		_dup2(p->prev_pipe_in, 0);
		_close(p->prev_pipe_in);
	}
	heredoc(c->redirections, p->std_in, false);
	if (p->has_pipe)
	{
		_dup2(p->fd_pipe[1], 1);
		_close(p->fd_pipe[1]);
		_close(p->fd_pipe[0]);
		redirection(c->redirections, false);
	}
	else
		redirection(c->redirections, false);
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
