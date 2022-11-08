/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/08 19:10:13 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// ft_charjoin
// - similar to ft_strjoin but join character
char	*ft_charjoin(char *str, char c)
{
	size_t	i;
	char	*ret;

	ret = malloc(sizeof(char) * (ft_strlen(str) + 2));
	if (!ret)
		ft_terminate("Error : malloc");
	i = 0;
	while (str[i] != 0)
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(str);
	return (ret);
}

// ft_chardup
// - make str which is started with specific char 
char	*ft_chardup(char c)
{
	char	*ret;

	ret = malloc(2);
	if (!ret)
		ft_terminate("Error : malloc");
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

// create_token
// - make token with prev_str & push back to list
// 1. make new node for token
// 2. init content of token
// 3. push back to list
void	create_token(char *prev_str, t_list *list)
{
	return ;
}

// read_quote_content
// - make str with quoted characters
// 1. ++line
// 2. ft_strdup("")
// 3. ft_charjoin() until next quote

char	*read_quote_content(char **line)
{
	char	*ret;

	return (ret);
}

// expand
// - make str by expanding env or wildcard
// 1. 

char	*expand(char **line)
{
	char	*ret;

	return (ret);
}
