/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/22 16:49:29 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/21 15:41:28 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "minishell_bonus.h"

static char	**put_program_name(char **old_command)
{
	char	**new_command;
	int		i;

	i = 0;
	while (old_command[i])
		++i;
	new_command = ft_calloc(sizeof(char *), i + 2);
	new_command[0] = ft_strdup("./minishell");
	i = 1;
	while (old_command[i - 1])
	{
		new_command[i] = ft_strdup(old_command[i - 1]);
		++i;
	}
	i = 0;
	while (old_command[i])
	{
		free(old_command[i]);
		++i;
	}
	free(old_command);
	return (new_command);
}

static void	set_program_path(t_context *c, t_list *env_list, bool is_subshell)
{
	if (is_subshell)
	{
		remove_bracket(*c->command);
		c->command = put_program_name(c->command);
	}
	else
		find_path(c->command, env_list);
}

pid_t	do_child_process(t_context *c, t_list *env_list,
	bool is_subshell, t_pipe *p)
{
	pid_t	pid;

	pid = _fork();
	if (pid != 0)
		return (pid);
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	set_child_pipe(p, c);
	if (*c->command == NULL)
		exit(0);
	if (is_builtin(*c->command) == true)
	{
		do_builtin(c->command, env_list, false);
		exit(g_exit_status >> 8);
	}
	set_program_path(c, env_list, is_subshell);
	if (execve(*c->command, c->command, list_to_2d_array(env_list)) == -1)
	{
		_write(2, "command not found\n", 19);
		exit(127);
	}
	return (pid);
}
