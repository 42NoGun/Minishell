/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/01 17:20:32 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

int	main(void)
{
	while (1)
	{
		char *str = readline("hello : ");
		if (!str)
		{
			printf("\033[1A"); // cursor line up
			printf("\033[10C"); // cursor move right
			printf("exit\n");
			exit(-1);
		}
		if (*str)
			add_history(str);
		free(str);
	}
	return (0);
}
