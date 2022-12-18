/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:10:23 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/18 01:52:54 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(t_list *env_list, char *env)
{
	t_node	*cur_node;
	int		env_len;

	cur_node = env_list->head;
	env_len = ft_strlen(env);
	while (cur_node)
	{
		if (env_len != 0 && ft_strncmp((char *)(cur_node->content),
			env, env_len) == 0)
		{
			return (ft_strchr((char *)cur_node->content, '=') + 1);
		}
		cur_node = cur_node->next;
	}
	return (NULL);
}

void	ft_setenv(t_list *env_list, char *key, char *value, char *command)
{
	t_node	*cur_node;
	char	*quoted_env;
	int		key_len;

	cur_node = env_list->head;
	key_len = ft_strlen(key);
	while (cur_node)
	{
		if (key_len && ft_strncmp((char *)(cur_node->content),
			key, key_len) == 0)
		{
			quoted_env = get_quoted_env(command);
			free(cur_node->content);
			cur_node->content = quoted_env;
			return ;
		}
		cur_node = cur_node->next;
	}
	return ;
}
