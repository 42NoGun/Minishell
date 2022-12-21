/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 20:38:00 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 15:13:36 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	get_int_len(long nb)
{
	size_t	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb *= -1;
		len++;
	}
	while (nb > 0)
	{
		nb /= 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char			*ptr;
	unsigned int	i;
	size_t			int_len;
	long			nb;

	nb = (long)n;
	int_len = get_int_len(nb);
	ptr = (char *)_malloc(sizeof(char) * (int_len + 1));
	i = int_len;
	ptr[i--] = 0;
	if (nb < 0)
	{
		ptr[0] = '-';
		nb *= -1;
	}
	if (nb == 0)
		ptr[0] = '0';
	while (nb > 0)
	{
		ptr[i--] = (nb % 10 + '0');
		nb /= 10;
	}
	return (ptr);
}
