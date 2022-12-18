/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:11:44 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/18 21:35:56 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_key(char *command, char *value)
{
	char	*key;

	key = ft_substr(command, 0, value - command);
	if (!key)
		ft_terminate("get_key, ft_substr");
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

char	*get_quoted_env(char *command)
{
	char	*quoted_env;
	char	*value;
	char	*key;

	value = get_value_env(command);
	if (!value)
		return (ft_strdup(command));
	key = get_key(command, value);
	value = ft_strdup(value);
	value = ft_strjoin_right_free("\"", value);
	value = ft_strjoin_left_free(value, "\"");
	quoted_env = ft_strjoin(key, value);
	return (quoted_env);
}

void	copy_envp(t_list *env_list, char **envp)
{
	int		i;
	char	*quoted_env;

	i = 0;
	while (envp[i])
	{
		quoted_env = get_quoted_env(envp[i]);
		push_back(env_list, make_node(quoted_env));
		++i;
	}
}
