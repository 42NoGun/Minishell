/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:38:21 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/15 15:01:43 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_ptr;

	lst_ptr = (t_list *)malloc(sizeof(t_list));
	if (!lst_ptr)
		return (0);
	lst_ptr->content = content;
	lst_ptr->next = NULL;
	return (lst_ptr);
}
