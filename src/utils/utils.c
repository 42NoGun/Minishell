/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:10:23 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/18 15:38:49 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *env_list, char *env)
{
	t_node	*cur_node;
	int		env_len;
	char	*tmp;

	cur_node = env_list->head;
	env_len = ft_strlen(env);
	while (cur_node)
	{
		if (env_len != 0 && ft_strncmp((char *)(cur_node->content),
			env, env_len) == 0)
		{
			tmp = ft_strchr((char *)cur_node->content, '=');
			if (tmp == NULL)
				return (NULL);
			return (tmp + 1);
		}
		cur_node = cur_node->next;
	}
	return (NULL);
}

void	ft_setenv(t_list *env_list, char *key, char *command)
{
	t_node	*cur_node;
	int		key_len;

	cur_node = env_list->head;
	key_len = ft_strlen(key);
	while (cur_node)
	{
		if (key_len && ft_strncmp((char *)(cur_node->content),
			key, key_len) == 0)
		{
			free(cur_node->content);
			cur_node->content = ft_strdup(command);
			return ;
		}
		cur_node = cur_node->next;
	}
	return ;
}
