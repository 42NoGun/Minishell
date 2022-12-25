/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:47 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/25 21:19:27 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <readline/readline.h>

static void	signal_interrupt(int signum)
{
	(void)signum;
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
