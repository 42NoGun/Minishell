/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 17:23:45 by jiyunpar         ###   ########.fr       */
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
#include <fcntl.h>
#include "minishell.h"


int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_list	*cmd_list;
	t_tree	*cmd_tree;
	t_list	*cmd_exec_list;
	t_list	*env_list;

	errno = 0;
	env_list = init_list();
	copy_envp(env_list, envp);
	if (argc >= 2)
	{
		subshell_logic(argc, argv, env_list);
		return (WEXITSTATUS(g_exit_status));
	}
	while (1)
	{
		define_signal();
		line = readline("minishell > ");
		signal(SIGINT, SIG_IGN);
		if (!line)
		{
			ft_putstr_fd("exit\n", 1);
			break ;
		}
		if (ft_strcmp(line, "") == 0)
		{
			free(line);
			continue ;
		}
		if (*line)
			add_history(line);
		if (is_correct_pair(line) == false)
		{
			free(line);
			continue ;
		}
		cmd_list = init_list();
		cmd_tree = init_tree();
		tokenize(line, cmd_list);
		parser(cmd_tree, cmd_list);
		if (check_syntax_error(cmd_tree) == false)
		{
			free_list_node_token(cmd_list);
			free_tree_node_field(cmd_tree);
			free(line);
			continue ;
		}
		cmd_exec_list = convert_tree_to_exec_list(cmd_tree);
		if (check_bracket_syntax_error(cmd_exec_list) == false)
		{
			free_list_node_token(cmd_list);
			free_tree_node_field(cmd_tree);
			free_list_only_node(cmd_exec_list);
			free(line);
			continue ;
		}
		pid_t pid = _fork();
		if (pid == 0)
		{
			signal(SIGINT, SIG_DFL);
			make_heredoc_file(cmd_exec_list);
			return (WEXITSTATUS(g_exit_status));
		}
		waitpid(pid, &g_exit_status, 0);
		if (WIFSIGNALED(g_exit_status) == true)
		{
			if (g_exit_status == 3)
				_write(2, "Quit: 3\n", 9);
			else if (g_exit_status == 2)
				_write(2, "\n", 1);
			g_exit_status = (g_exit_status + 128) << 8;
			free_list_node_token(cmd_list);
			free_tree_node_field(cmd_tree);
			free_list_only_node(cmd_exec_list);
			free(line);
			continue ;
		}
		signal(SIGINT, SIG_IGN);
		execute(cmd_exec_list, env_list);
		free_list_node_token(cmd_list);
		free_tree_node_field(cmd_tree);
		free_list_only_node(cmd_exec_list);
		free(line);
		system("leaks minishell");
	}
	free_list_node_content(env_list);
	return (0);
}
