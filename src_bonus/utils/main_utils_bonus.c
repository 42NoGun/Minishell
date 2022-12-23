/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 11:49:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 16:54:52 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	line = readline("minishell > ");
	signal(SIGINT, SIG_IGN);
	return (line);
}

bool	has_line_content(char *line)
{
	if (ft_strcmp(line, "") == 0)
		return (false);
	return (true);
}

bool	is_line_null(char *line)
{
	if (!line)
		return (true);
	return (false);
}

int	add_history_line(char *line)
{
	add_history(line);
	return (1);
}
