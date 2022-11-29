/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/29 14:33:50 by jiyunpar         ###   ########.fr       */
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
	t_list	*cmd_list;
	t_tree	*cmd_tree;

	errno = 0;
	cmd_list = init_list();
	cmd_tree = init_tree();
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
			ft_putstr_fd("minishell : syntax error\n", 2);
			free(line);
			continue ;
		}
		tokenize(line, cmd_list); // parser 안으로
		// syntax_check(cmd_list);
		parser(cmd_tree, cmd_list);
		check_syntax_error(cmd_tree); // parser 안으로
		free(line);
	}
	return (0);
}
