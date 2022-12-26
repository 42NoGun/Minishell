/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_dollar.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/26 13:46:45 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_content(char *content, t_list *env_list, char **command)
{
	char	*expanded_content;
	char	*content_init_pos;

	content_init_pos = content;
	expanded_content = ft_strdup("");
	while (*content)
	{
		concatenate_not_expanded_content(&expanded_content, &content);
		if (!*content)
			break ;
		++content;
		concatenate_expanded_content(&expanded_content, &content,
			command, env_list);
	}
	free(content_init_pos);
	return (expanded_content);
}

static void	concatenate_string(char **command, char **quote_content,
	char **expanded_command, t_list *env_list)
{
	if (**command == '\'')
	{
		*quote_content = read_quote_content(command, '\'');
		*expanded_command = ft_strjoin(*expanded_command, *quote_content);
	}
	else if (**command == '"')
	{
		*quote_content = read_quote_content(command, '\"');
		*quote_content = expand_content(*quote_content, env_list, command);
		*expanded_command = ft_strjoin(*expanded_command, *quote_content);
	}
	else
	{
		*quote_content = read_not_quote_content(command);
		*quote_content = expand_content(*quote_content, env_list, command);
		*expanded_command = ft_strjoin(*expanded_command, *quote_content);
	}
}

char	*read_not_quote_content(char **line)
{
	char	*content;
	size_t	len;

	len = 0;
	while (**line && !(**line == '"' || **line == '\''))
	{
		++(*line);
		++len;
	}
	content = ft_substr(*line - len, 0, len);
	*line -= 1;
	return (content);
}

void	expand_dollar(t_token *token, t_list *env_list)
{
	char	*command;
	char	*quote_content;
	char	*expanded_command;

	expanded_command = ft_strdup("");
	command = token->value;
	while (*command)
	{
		concatenate_string(&command, &quote_content,
			&expanded_command, env_list);
		++command;
	}
	free(token->value);
	token->value = expanded_command;
}
