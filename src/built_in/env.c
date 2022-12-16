/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:57 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/16 11:53:53 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_key(char *command, char *value)
{
	char	*key;

	key = ft_substr(command, 0, value - command);
	if (!key)
		ft_terminate("get_key, ft_substr");
	return (key);
}

static char	*get_value(char *command)
{
	char	*value;

	value = ft_strchr(command, '=');
	if (!value)
		return (NULL);
	return (value + 1);
}

// h="hello";
// key : h=
// value : "hello"
static char	*get_not_quoted_env(char *command)
{
	char	*not_quoted_env;
	char	*value;
	char	*key;

	value = get_value(command);
	if (!value)
		return (command);
	key = get_key(command, value);
	value = ft_substr(value, 1, ft_strlen(value + 1) - 1);
	not_quoted_env = ft_strjoin(key, value);
	return (not_quoted_env);
}

void	b_env(char **command, t_list *env_list)
{
	t_node	*cur_node;
	char	*value;
	char	*not_quoted_env;
	int		i;

	cur_node = env_list->head;
	if (command[1] != NULL)
	{
		ft_putendl_fd("env: Have argument", 2);
	}
	while (cur_node)
	{
		value = ft_strchr(cur_node->content, '=');
		if (value != NULL)
		{
			not_quoted_env = get_not_quoted_env(cur_node->content);
			ft_putendl_fd(not_quoted_env, 1);
		}
		cur_node = cur_node->next;
	}
}
