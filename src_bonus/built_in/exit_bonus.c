/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 13:53:25 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/27 10:27:13 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// exit
// - when exit built-in execute in child process, don't print "exit" on terminal
// - argument > INT = undefined behavior;

static bool	command_has_alpha(char *command)
{
	int	i;

	i = 0;
	if (command == NULL)
		return (false);
	if (command[0] == '-' || command[0] == '+')
		++i;
	while (command[i])
	{
		if (!ft_isdigit(command[i]))
			return (true);
		++i;
	}
	return (false);
}

int	b_exit(char **command, bool parent)
{
	int	i;

	if (parent)
		ft_putendl_fd("exit", 2);
	if (command[1] == NULL)
		exit(0);
	if (ft_strcmp(command[1], "--") == 0)
		exit(0);
	i = 0;
	while (command[i])
		i++;
	if (i > 2)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putendl_fd("Too many arguments", 2);
		return (1);
	}
	if (command_has_alpha(command[1]) == true)
	{
		ft_putstr_fd("exit: ", 2);
		ft_putendl_fd("numeric argument required", 2);
		exit(2);
	}
	exit(ft_atoi(command[1]));
}
