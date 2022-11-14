/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 15:40:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/14 16:20:40 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*

int	get_priority(char *prev_str)
{
	if (ft_strcmp(prev_str, "||") == 0)
		return (0);
	if (ft_strcmp(prev_str, "&&") == 0)
		return (0);
	if (ft_strcmp(prev_str, "|") == 0)
		return (1);
	if (ft_strcmp(prev_str, ">>") == 0)
		return (1);
	if (ft_strcmp(prev_str, "<<") == 0)
		return (1);
	if (ft_strcmp(prev_str, ">") == 0)
		return (1);
	if (ft_strcmp(prev_str, "<") == 0)
		return (1);
	return (2);
}


### Syntax에러로 볼 것
- >&, >|, |&, <&
- |||, >>>, <<<
- echo (word), echo ($word)
- 짝 안맞는 괄호, 쿼트

- 처음에 나올 수 있음 : <,  >, <<, >>
- 처음에 나오면 안되는 operator : ||, &&, |, >(이것만), <(이것만), <<(이것만), >>(이것만)
| > >> 

1. list->len == 1, 우선 순위가 0이나 1이면 안된다.
2. 

*/
void	check_syntax(t_list *cmd_list)
{
	t_node	*cur_node;

	cur_node = cmd_list->head;
	while (cur_node)
	{
		
		cur_node = cur_node->next;
	}
}