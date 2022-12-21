/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_no_free.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 09:49:30 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 16:48:28 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_no_free(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*ptr;

	ptr = (char *)_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 1);
	i = 0;
	while (s1[i] != 0)
	{
		ptr[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != 0)
	{
		ptr[i + j] = s2[j];
		j++;
	}
	ptr[i + j] = 0;
	return (ptr);
}
