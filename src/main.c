/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 15:09:409 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>
#include <errno.h>
#include "../include/minishell.h"

int	main(int argc, char **argv)
{
	char	*line;

	errno = 0;
	while (1)
	{
		line = readline("minishell > ");
		if (!line)
		{
			printf("\033[1A");
			printf("\033[13C");
			printf("exit\n");
			exit(0);
		}
		if (*line)
			add_history(line);
		if (is_correct_pair(line))
		{
			printf("wrong\n");
			free(line);
			continue ;
		}
		tokenize(line);
		free(line);
	}
	return (0);
}
