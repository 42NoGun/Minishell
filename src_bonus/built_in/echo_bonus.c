/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:55 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/23 17:12:29 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

int	b_echo(char **command)
{
	bool	print_newline;
	int		i;

	print_newline = true;
	i = 1;
	while (command[i] && ft_strcmp(command[i], "-n") == 0)
	{
		print_newline = false;
		++i;
	}
	while (command[i])
	{
		ft_putstr_fd(command[i], 1);
		if (command[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		++i;
	}
	if (print_newline)
		ft_putchar_fd('\n', 1);
	return (0);
}
