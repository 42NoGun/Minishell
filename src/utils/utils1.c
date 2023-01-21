/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:11:44 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/21 16:05:01 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *command, char *value)
{
	char	*key;

	key = ft_substr(command, 0, value - command);
	return (key);
}

char	*get_value_env(char *command)
{
	char	*value;

	value = ft_strchr(command, '=');
	if (!value)
		return (NULL);
	return (value + 1);
}

char	*get_value_export(char *command)
{
	char	*value;

	value = ft_strchr(command, '=');
	if (!value)
		return (NULL);
	return (value);
}

void	copy_envp(t_list *env_list, char **envp)
{
	int		i;

	i = 0;
	while (envp[i])
	{
		push_back(env_list, make_node(ft_strdup(envp[i])));
		++i;
	}
}
