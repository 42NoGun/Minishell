/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/25 21:15:00 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_priority(char *prev_str)
{
	if (ft_strcmp(prev_str, "||") == 0)
		return (0);
	if (ft_strcmp(prev_str, "&&") == 0)
		return (0);
	if (ft_strcmp(prev_str, "|") == 0)
		return (1);
	return (2);
}

// create_token
// - make token with prev_str & push back to list
// 1. make new node for token
// 2. init content of token
// 3. push back to list
static t_token	*create_token(char *prev_str)
{
	t_token	*token;

	token = _malloc(sizeof(t_token));
	token->value = prev_str;
	token->priority = get_priority(prev_str);
	return (token);
}

// ft_charjoin
// - similar to ft_strjoin but join character
char	*ft_charjoin(char *str, char c)
{
	size_t	i;
	char	*ret;

	ret = _malloc(sizeof(char) * (ft_strlen(str) + 2));
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

	ret = _malloc(2);
	ret[0] = c;
	ret[1] = '\0';
	return (ret);
}

void	put_token_in_list(char *prev_str, t_list *list)
{
	t_node	*node;

	if (!*prev_str)
	{
		free(prev_str);
		return ;
	}
	node = make_node(create_token(prev_str));
	push_back(list, node);
}
