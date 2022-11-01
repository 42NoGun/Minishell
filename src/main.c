/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/01 15:05:28 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <stdlib.h>
#include <signal.h>
#include <termios.h>
#include <unistd.h>

// struct termios old;
// struct termios new;
// void set_input_mode(void)
// {
// 		tcgetattr(STDIN_FILENO, &new); // STDIN으로부터 터미널 속성을 받아온다
// 		new.c_lflag &= ~(ECHO);  // ICANON, ECHO 속성을 off
// 		new.c_cc[VMIN] = 1;               // 1 바이트씩 처리
// 		new.c_cc[VTIME] = 0;              // 시간은 설정하지 않음
// 		tcsetattr(STDIN_FILENO, TCSANOW, &new); // 변경된 속성의 터미널을 STDIN에 바로 적용
// }
// void sig_handler(int signal)
// {
//     printf("signal : %d\n", signal);
//     if (signal == SIGINT)
//     {
//         printf("\nnnoshell$");
//     }
//     else if (signal == SIGTERM)
//     {
//         printf(" exit\n");
//         exit(-1);    
// 	}
// }

// void setting_signal()
// {
//     signal(SIGINT, sig_handler);  // CTRL + C
//     signal(SIGTERM, sig_handler); // CTRL + D
//     signal(SIGQUIT, sig_handler); // CTRL + /
// }

int	main(void)
{
	// setting_signal();
	// set_input_mode();
	while (1)
	{

	char *str = readline("hello : ");
	if (!str)
	{
		rl_replace_line("", 0);
		write(1, "exit\n", 5);
		exit(0);
	}

	// printf("%s|\n", str);
	}
	return (0);
}