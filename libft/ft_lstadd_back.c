/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:05:39 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/19 14:57:59 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*lst_last;

	if (new == 0)
		return ;
	else
	{
		if (*lst == 0)
		{
			*lst = new;
			return ;
		}
		lst_last = ft_lstlast(*lst);
		lst_last->next = new;
	}
}
