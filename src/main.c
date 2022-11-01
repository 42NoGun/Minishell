/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/01 15:54:16 by cheseo           ###   ########.fr       */
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
	// setting_signal();
	// set_input_mode();
	while (1)
	{

	char *str = readline("hello : ");
	if (!str)
	{
		//rl_replace_line("", 0);
		//write(1, "exit\n", 5);
		//exit(0);
		printf("\033[1A");
        printf("\033[7C");
        printf("exit\n");
        exit(-1);
	}

	// printf("%s|\n", str);
	}
	return (0);
}
