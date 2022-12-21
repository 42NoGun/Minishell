/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 14:38:21 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 15:14:12 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*lst_ptr;

	lst_ptr = (t_list *)_malloc(sizeof(t_list));
	lst_ptr->content = content;
	lst_ptr->next = NULL;
	return (lst_ptr);
}
