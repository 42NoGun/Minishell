/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:20:21 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/14 16:52:58 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

    //push_left(NULL, make_tree_node(cur_node->content), cmd_tree);
    //cur_node = cur_node->next;
void	parser(t_tree *cmd_tree, t_list *cmd_list)
{
    t_node  *cur_node;
    t_token *token;
    
    cur_node = cmd_list->head;
    while (cur_node)
    {
        token = cur_node->content;
        while (token->priority == 2)
        {
            // 여기서 합치고     

            cur_node = cur_node->next;
        }
        if (token->priority == 1 || token->priority == 0)
        {
            // 트리에 담고 다음으로 
        }
        cur_node = cur_node->next;
    }
}
