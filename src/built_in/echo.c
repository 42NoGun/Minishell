/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:55 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/09 16:55:07 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_echo(char **commands)
{
	int	i;

	// echo -n -n -n 
	if (commands[1] == NULL)
	{
		printf("\n");
		return ;
	}
	i = 1;
	while (commands[i])
	{
		if (ft_strcmp(commands[i], "-n") != 0)
		{
			printf("%s", commands[i]);
			if (commands[i + 1] != NULL)
				printf(" ");
		}
		++i;
	}
	if (ft_strcmp(commands[1], "-n") != 0)
		printf("\n");
}