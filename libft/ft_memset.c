/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/06 14:54:30 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/16 15:49:47 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *ptr, int value, size_t len)
{
	unsigned char	*new_ptr;

	new_ptr = (unsigned char *)ptr;
	while (len--)
	{
		*new_ptr = (unsigned char)value;
		new_ptr++;
	}
	return (ptr);
}
