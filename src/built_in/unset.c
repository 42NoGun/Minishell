/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:15 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/24 13:12:52 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_delete_env(t_list *env_list, char *key)
{
	t_node	*cur_node;
	t_node	*next_node;
	int		key_len;

	cur_node = env_list->head;
	key_len = ft_strlen(key);
	while (cur_node)
	{
		next_node = cur_node->next;
		if (key_len && ft_strncmp((char *)(cur_node->content),
			key, key_len) == 0)
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

// unset
// -delete variable from env_list
int	b_unset(char **command, t_list *env_list)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (command[i])
	{
		value = get_value_env(command[i]);
		key = get_key(command[i], value);
		ft_delete_env(env_list, key);
		free(key);
		++i;
	}
	return (0);
}
