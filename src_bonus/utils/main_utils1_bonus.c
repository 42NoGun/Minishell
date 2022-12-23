/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils1_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:49:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 17:17:21 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

bool	is_catched_interrupt(t_list *cmd_list)
{
	if (WIFSIGNALED(g_exit_status) == true)
	{
		if (g_exit_status == 3)
			_write(2, "Quit: 3\n", 9);
		else if (g_exit_status == 2)
			_write(2, "\n", 1);
		g_exit_status = (g_exit_status + 128) << 8;
		free_list_node_token(cmd_list);
		return (true);
	}
	signal(SIGINT, SIG_IGN);
	return (false);
}

void	make_heredoc(t_list *cmd_list)
{
	pid_t	pid;

	pid = _fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		make_heredoc_file(cmd_list);
		exit(WEXITSTATUS(g_exit_status));
	}
	waitpid(pid, &g_exit_status, 0);
}
