/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/06 15:55:52 by jiyunpar         ###   ########.fr       */
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
#include "minishell.h"

// void	subshell_logic(int argc, char **argv, char **envp)
// {
// 	int	i;

// 	char *line;
// 	line = ft_strjoin(argv[0]);
// 	tokenize(line, cmd_list); // parser 안으로
// 	// syntax_check(cmd_list);
// 	parser(cmd_tree, cmd_list);
// 	check_syntax_error(cmd_tree); // parser 안으로
// 	free(line);
// }

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_list *cmd_list;
	t_tree *cmd_tree;

	errno = 0;
	// if (argc > 2)
	// {
	// 	subshell_logic(argc, argv, envp);
	// 	return (0);
	// }
	while (1)
	{
		cmd_list = init_list();
		cmd_tree = init_tree();
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
		if (is_correct_pair(line) == false)
		{
			free(line);
			continue;
		}
		tokenize(line, cmd_list);
		parser(cmd_tree, cmd_list);
		if (check_syntax_error(cmd_tree) == false)
		{
			free(line);
			continue;
		}
		execute(convert_tree_to_exec_list(cmd_tree), envp);
		free(line);
	}
	return (0);
}
