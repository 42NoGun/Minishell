/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_builtin_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:15:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 17:12:20 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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
