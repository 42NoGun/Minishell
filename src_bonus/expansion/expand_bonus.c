/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 11:26:17 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_field(t_field *field, t_list *env_list, bool is_subshell)
{
	int		len;
	t_token	*cur_token;
	t_node	*cur_node;

	len = field->len;
	cur_node = field->start_ptr;
	if (is_subshell)
		return ;
	while (len)
	{
		cur_token = (t_token *)cur_node->content;
		expand_dollar(cur_token, env_list);
		expand_wildcard(cur_token);
		cur_node = cur_node->next;
		--len;
	}
}
