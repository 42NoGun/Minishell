/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/07 11:50:46 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/18 13:29:04 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*new_s;

	new_s = (unsigned char *)s;
	if (n == 0)
		return ;
	while (n--)
	{
		*new_s = 0;
		new_s++;
	}	
}
