/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:43:12 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/20 15:46:06 by cheseo           ###   ########.fr       */
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

t_cmd_tool	*init_cmd_tool(t_cmd_tool *cmd_tool)
{
	cmd_tool->cmd_list = init_list();
	cmd_tool->cmd_tree = init_tree();
	return (cmd_tool);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_list		*env_list;
	t_cmd_tool	*cmd_tool;

	errno = 0;
	cmd_tool = malloc(sizeof(t_cmd_tool));
	cmd_tool = init_cmd_tool(cmd_tool);
	env_list = init_list();
	copy_envp(env_list, envp);
	if (argc >= 2)
		return (run_subshell(argc, argv, env_list));
	while (1)
	{
		define_signal();
		line = readline("minishell > ");
		signal(SIGINT, SIG_IGN);
		if (!is_cmd_input(line))
		{
			end_program(env_list);
			break ;
		}
		else
			if (!is_executable_command(line))
				continue ;
		init_cmd_tool(cmd_tool);
		tokenize(line, cmd_tool->cmd_list);
		parser(cmd_tool->cmd_tree, cmd_tool->cmd_list);
		if (check_syntax_error(cmd_tool->cmd_tree) == false)
		{
			free_cmd_tool(cmd_tool);
			continue ;
		}
		cmd_tool->cmd_exec_list = convert_tree_to_exec_list(cmd_tool->cmd_tree);
		if (check_bracket_syntax_error(cmd_tool->cmd_exec_list) == false)
		{
			free_cmd_tool(cmd_tool);
			continue ;
		}
		if (making_heredoc(cmd_tool))
			continue ;
		signal(SIGINT, SIG_IGN);
		execute(cmd_tool->cmd_exec_list, env_list);
		free_cmd_tool(cmd_tool);
	}
	free_cmd_tool(cmd_tool);
	free(cmd_tool);
	free_list_node_content(env_list);
	return (0);
}
