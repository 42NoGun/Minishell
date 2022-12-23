/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:30:18 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/23 11:27:21 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdbool.h>
#include "libft.h"

void	remove_bracket(char *command)
{
	ft_memmove(command, command + 1, ft_strlen(command));
	command[ft_strlen(command) - 1] = 0;
}

bool	is_pipe(char *cmd)
{
	if (ft_strcmp(cmd, "|") == 0)
		return (true);
	return (false);
}

bool	is_logical_and(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0)
		return (true);
	return (false);
}

bool	is_logical_or(char *cmd)
{
	if (ft_strcmp(cmd, "||") == 0)
		return (true);
	return (false);
}

bool	is_builtin(char	*command)
{
	if (!command)
		return (false);
	if (ft_strcmp(command, "echo") == 0)
		return (true);
	if (ft_strcmp(command, "cd") == 0)
		return (true);
	if (ft_strcmp(command, "pwd") == 0)
		return (true);
	if (ft_strcmp(command, "export") == 0)
		return (true);
	if (ft_strcmp(command, "unset") == 0)
		return (true);
	if (ft_strcmp(command, "env") == 0)
		return (true);
	if (ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}
