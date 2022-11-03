/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/08 16:45:06 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/18 10:30:22 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t		i;
	size_t		j;

	if (ft_strlen(needle) == 0)
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != 0 && i + ft_strlen(needle) <= len)
	{
		j = 0;
		while (needle[j] != 0)
		{
			if (haystack[i + j] == needle[j])
			{
				j++;
				if (j == ft_strlen(needle))
					return ((char *)&haystack[i]);
			}
			else
				break ;
		}		
		i++;
	}
	return (0);
}
