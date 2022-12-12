/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:55 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/12 14:52:10 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(char **command)
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
}
