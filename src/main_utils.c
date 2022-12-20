/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:57:52 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/20 15:39:28 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>
#include <readline/history.h>

int	run_subshell(int argc, char **argv, t_list *env_list)
{
	subshell_logic(argc, argv, env_list);
	return (WEXITSTATUS(g_exit_status));
}

int	end_program(t_list *env_list)
{
	ft_putstr_fd("exit\n", 1);
	free_list_node_content(env_list);
	return (0);
}

int	make_heredoc_process(t_list *cmd_exec_list)
{
	signal(SIGINT, SIG_DFL);
	make_heredoc_file(cmd_exec_list);
	return (WEXITSTATUS(g_exit_status));
}

bool	is_cmd_input(char *line)
{
	if (line)
		return (true);
	return (false);
}

bool	is_executable_command(char *line)
{
	int	is_not_empty_line;

	is_not_empty_line = ft_strcmp(line, "");
	if (is_not_empty_line)
		add_history(line);
	if (!is_not_empty_line || !is_correct_pair(line))
	{
		free(line);
		return (false);
	}
	return (true);
}

void	free_cmd_tool(t_cmd_tool *cmd_tool)
{
	if (cmd_tool->cmd_list)
		free_list_node_token(cmd_tool->cmd_list);
	if (cmd_tool->cmd_tree)
		free_tree_node_field(cmd_tool->cmd_tree);
	if (cmd_tool->cmd_exec_list)
		free_list_only_node(cmd_tool->cmd_exec_list);
}

bool	making_heredoc(t_cmd_tool *cmd_tool)
{
	pid_t	pid;

	pid = fork();
	if (pid == 0)
		return (make_heredoc_process(cmd_tool->cmd_exec_list));
	waitpid(pid, &g_exit_status, 0);
	if (WIFSIGNALED(g_exit_status) == true)
	{
		if (g_exit_status == 3)
			write(2, "Quit: 3\n", 9);
		else if (g_exit_status == 2)
			write(2, "\n", 1);
		g_exit_status = (g_exit_status + 128) << 8;
		free_cmd_tool(cmd_tool);
		return (true);
	}
	return (false);
}

void	execute_command(t_cmd_tool *cmd_tool, t_list *env_list)
{
	signal(SIGINT, SIG_IGN);
	execute(cmd_tool->cmd_exec_list, env_list);
	free_cmd_tool(cmd_tool);
}
