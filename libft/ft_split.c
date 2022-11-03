/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/14 13:28:30 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/07/19 14:56:53 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	count_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	cnt;

	i = 0;
	cnt = 0;
	while (s[i] != 0)
	{
		while (s[i] != 0 && s[i] == c)
			i++;
		if (s[i] != 0 && s[i] != c)
			cnt++;
		while (s[i] != 0 && s[i] != c)
			i++;
	}
	return (cnt);
}

static unsigned int	get_word_len(char const *s, char c)
{
	unsigned int	len;

	len = 0;
	while (s[len] != 0 && s[len] != c)
		len++;
	return (len);
}

static char	*make_word(char const *s, char c)
{
	unsigned int	i;
	unsigned int	word_len;
	char			*word;

	i = 0;
	word_len = get_word_len(s, c);
	word = (char *)malloc(sizeof(char) * (word_len + 1));
	if (!word)
		return (0);
	while (i < word_len)
	{
		word[i] = s[i];
		i++;
	}
	word[i] = 0;
	return (word);
}

static char	**do_free(char **list)
{
	unsigned int	i;

	i = 0;
	while (list[i])
	{
		free(list[i++]);
	}
	free(list);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char			**list;
	unsigned int	word_cnt;
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	word_cnt = count_word(s, c);
	list = (char **)malloc(sizeof(char *) * (word_cnt + 1));
	if (!list)
		return (0);
	while (i < word_cnt)
	{
		while (s[j] != 0 && s[j] == c)
			j++;
		list[i] = make_word(&s[j], c);
		if (!list[i])
			return (do_free(list));
		while (s[j] != 0 && s[j] != c)
			j++;
		i++;
	}
	list[i] = 0;
	return (list);
}
