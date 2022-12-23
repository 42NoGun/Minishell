/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:57 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/23 17:12:34 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

// env
// - env_list is doubly linked list
// - each node has string value as below
// ex) USER=jiyunpar -> unquoted key & unquoted value
// 1. print list which is unorderd
int	b_env(char **command, t_list *env_list)
{
	t_node	*cur_node;
	char	*value;

	cur_node = env_list->head;
	if (command[1] != NULL)
	{
		ft_putendl_fd("env: Have argument", 2);
		return (127);
	}
	while (cur_node)
	{
		value = ft_strchr(cur_node->content, '=');
		if (value != NULL)
		{
			ft_putendl_fd(cur_node->content, 1);
		}
		cur_node = cur_node->next;
	}
	return (0);
}
