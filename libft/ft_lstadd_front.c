/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 15:13:28 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/18 17:42:04 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (new == 0)
		return ;
	else
	{
		if (*lst == 0)
		{
			*lst = new;
			return ;
		}
		new->next = *lst;
		*lst = new;
	}
}
