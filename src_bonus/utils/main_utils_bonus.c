/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:49:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/18 21:25:45 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <readline/readline.h>
#include <readline/history.h>

t_list	*init_environment(char **envp)
{
	t_list	*env_list;

	errno = 0;
	env_list = init_list();
	copy_envp(env_list, envp);
	return (env_list);
}

char	*get_line(void)
{
	char	*line;

	define_signal();
	line = readline("minishell$ ");
	signal(SIGINT, SIG_IGN);
	return (line);
}

bool	has_line_content(char *line)
{
	while (*line && *line == ' ')
		++line;
	if (ft_strcmp(line, "") == 0)
		return (false);
	return (true);
}

bool	is_line_null(char *line)
{
	if (!line)
	{
		ft_putstr_fd("exit\n", 1);
		return (true);
	}
	return (false);
}

int	add_history_line(char *line)
{
	add_history(line);
	return (1);
}
