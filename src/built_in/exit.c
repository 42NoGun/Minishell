/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:53:25 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/14 15:46:22 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_exit(char **command, bool parent)
{
	int	i;

	if (parent)
		ft_putendl_fd("exit", 2);
	i = 0;
	while (command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putendl_fd("Too many arguments", 2);
		g_exit_status = 1 << 8;
		return ;
	}
	if (command[1] == NULL)
		exit(0);
	exit(ft_atoi(command[1]));
}
