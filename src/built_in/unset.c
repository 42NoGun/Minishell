/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:15 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/16 13:14:17 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_env(t_list *env_list, char *key)
{
	t_node	*cur_node;
	t_node	*next_node;
	int		key_len;

	cur_node = env_list->head;
	key_len = ft_strlen(key);
	while (cur_node)
	{
		next_node = cur_node->next;
		if (key_len && ft_strncmp((char *)(cur_node->content), key, key_len) == 0)
		{
			free(cur_node->content);
			if (cur_node == env_list->head)
				pop_front(env_list);
			else if (cur_node == env_list->tail)
				pop_back(env_list);
			else
				pop_middle(env_list, cur_node);
		}
		cur_node = next_node;
	}
}

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
	return (value);
}

void	b_unset(char **command, t_list *env_list)
{
	int		i;
	char 	*key;
	char 	*value;
	char 	*quoted_env;

	i = 1;
	while (command[i])
	{
		value = get_value(command[i]);
		key = get_key(command[i], value);
		ft_delete_env(env_list, key);
		free(key);
		++i;
	}
}