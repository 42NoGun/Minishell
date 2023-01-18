/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:55 by cheseo            #+#    #+#             */
/*   Updated: 2023/01/18 16:00:39 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

bool	is_option(char *str)
{
	if (ft_strncmp(str, "-n", 2) == 0)
	{
		str += 2;
		while (*str)
		{
			if (*str != 'n')
				return (false);
			++str;
		}
		return (true);
	}
	return (false);
}

int	b_echo(char **command)
{
	bool	print_newline;
	int		i;

	print_newline = true;
	i = 1;
	while (command[i] && is_option(command[i]))
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
