/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 10:24:26 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/19 11:16:40 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(const char c, char const *set)
{
	unsigned int	i;

	i = 0;
	while (set[i] != 0)
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static size_t	get_start(char const *s1, char const *set)
{
	size_t	start;

	start = 0;
	while (s1[start] != 0 && is_charset(s1[start], set))
		start++;
	return (start);
}

static size_t	get_end(char const *s1, char const *set)
{
	size_t	end;
	size_t	s_len;

	s_len = ft_strlen(s1);
	end = s_len - 1;
	while (end > 0 && is_charset(s1[end], set))
		end--;
	return (end);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	start;
	size_t	end;
	size_t	len;
	char	*ptr;

	start = get_start(s1, set);
	end = get_end(s1, set);
	if (start > end)
		len = 0;
	else
		len = end - start + 1;
	ptr = ft_substr(s1, (unsigned int)start, len);
	return (ptr);
}
