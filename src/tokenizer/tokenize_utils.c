/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 16:26:26:00 by cheseo           ###   ########.fr       */
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

int	get_priority(char *prev_str)
{
	if (ft_strcmp(prev_str, "||") == 0)
		return (0);
	if (ft_strcmp(prev_str, "&&") == 0)
		return (0);
	if (ft_strcmp(prev_str, "|") == 0)
		return (1);
	if (ft_strcmp(prev_str, ">>") == 0)
		return (1);
	if (ft_strcmp(prev_str, "<<") == 0)
		return (1);
	if (ft_strcmp(prev_str, ">") == 0)
		return (1);
	if (ft_strcmp(prev_str, "<") == 0)
		return (1);
	return (2);
}

// create_token
// - make token with prev_str & push back to list
// 1. make new node for token
// 2. init content of token
// 3. push back to list
t_token	*create_token(char *prev_str)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	if (!token)
		ft_terminate("creat_token, malloc error");
	token->value = prev_str;
	token->priority = get_priority(prev_str);
	return (token);
}

void	put_token_in_list(char *prev_str, t_list *list)
{
	t_node	*node;

	node = make_node(create_token(prev_str));
	push_back(list, node);
}

// read_quote_content
// - make str with quoted characters
// 1. ++line
// 2. ft_strdup("")
// 3. ft_charjoin() until next quote

char	*read_quote_content(char **line, char quote)
{
	char	*quote_content;
	size_t	len;

	len = ft_strchr((*line + 1), quote) - *line + 1;
	quote_content = ft_substr(*line, 0, len);
	*line += len;
	return (quote_content);
}

// expand
// - make str by expanding env or wildcard
// 1. 

char	*expand(char **line)
{
	(void) line;
	char *ret = NULL;

	return (ret);
}
