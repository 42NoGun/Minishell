/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:57 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/12 16:52:07 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	b_env(char **command, t_list *env_list)
{
	t_node	*cur_node;
	char	*value;
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
			ft_putendl_fd(cur_node->content, 1);
		cur_node = cur_node->next;
	}
}
