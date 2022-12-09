/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/09 15:13:43 by cheseo           ###   ########.fr       */
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

void	subshell_logic(int argc, char **argv, char **envp)
{
	int	i;

	t_list *cmd_list;
	t_tree *cmd_tree;
	char *line;

	cmd_list = init_list();
	cmd_tree = init_tree();
	line = ft_strdup(argv[1]);
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return ;
	}
	if (is_correct_pair(line) == false)
	{
		free(line);
		return ;
	}
	tokenize(line, cmd_list);
	parser(cmd_tree, cmd_list);
	if (check_syntax_error(cmd_tree) == false)
	{
		free(line);
		return ;
	}
	execute(convert_tree_to_exec_list(cmd_tree), envp);
	free(line);
}

void	signal_interrupt(int signum)
{
	g_exit_status = 130 << 8;
	printf("\n");
	if (rl_on_new_line() == -1)
		exit(1);
    rl_replace_line("", 10);
   	rl_redisplay();
}

void	define_signal(void)
{
	signal(SIGINT, signal_interrupt);
	signal(SIGQUIT, SIG_IGN);
}

int main(int argc, char **argv, char **envp)
{
	char *line;
	t_list *cmd_list;
	t_tree *cmd_tree;

	errno = 0;
	if (argc >= 2)
	{
		subshell_logic(argc, argv, envp);
		return (WEXITSTATUS(g_exit_status));
	}

	while (1)
	{
		define_signal();
		cmd_list = init_list();
		cmd_tree = init_tree();
		//hello("minishell > "); 
// 		if (WIFSIGNALED(g_exit_status) == true)
// 		{
// 			printf("\n");
// //			printf("\033[1A");
// 	//		printf("\033[13C");		
// 		}
		line = readline("minishell > ");
		signal(SIGINT, SIG_IGN);
		if (!line)
		{
			// printf("\033[1A");
			// printf("\033[13C");
			printf("exit\n");
			exit(0);
		}
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			// g_exit_status = 127
			continue ;
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
