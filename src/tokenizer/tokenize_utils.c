/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: junji <junji@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 15:09:40 by junji            ###   ########.fr       */
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

int ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s1 == *s2)
	{
		++s1;
		++s2;
	}
	return (*s1 - *s2);
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

// enum e_operator	get_type(char *prev_str)
// {
// 	if (ft_strcmp(prev_str, "||") == 0)
// 		return (OR);
// 	if (ft_strcmp(prev_str, "&&") == 0)
// 		return (AND);
// 	if (ft_strcmp(prev_str, "|") == 0)
// 		return (PIPE);
// 	if (ft_strcmp(prev_str, ">>") == 0)
// 		return (OUT_REDIR_APPEND);
// 	if (ft_strcmp(prev_str, "<<") == 0)
// 		return (HEREDOC);
// 	if (ft_strcmp(prev_str, ">") == 0)
// 		return (OUT_REDIR);
// 	if (ft_strcmp(prev_str, "<") == 0)
// 		return (IN_REDIR);
// 	if (ft_strcmp(prev_str, "\"") == 0)
// 		return (DOUBLE_QUOTE);
// 	if (ft_strcmp(prev_str, "'") == 0)
// 		return (SINGLE_QUOTE);
// 	if (ft_strcmp(prev_str, "(") == 0)
// 		return (OPEN_BRACKET);
// 	if (ft_strcmp(prev_str, "*") == 0)
// 		return (WILDCARD);
// 	if (ft_strcmp(prev_str, "$?") == 0)
// 		return (Q_MARK);
// 	if (ft_strcmp(prev_str, "$") == 0)
// 		return (DOLLAR);
// 	return (CMD);
	
// }

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
	// token->type = get_type(prev_str);
	return (token);
}

void	put_token_in_list(char *prev_str, t_list *list)
{
	t_node	*node;

	node = make_node(create_token(prev_str));
	push_back(list, node)
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
