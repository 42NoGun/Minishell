/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/17 09:00:32 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

bool	is_matchable_asterisk(char *dst_file, char *src_file)
{
	while (*dst_file || *src_file)
	{
		if (*src_file == '*')
		{
			while (*src_file == '*')
				++src_file;
				dst_file = ft_strchr(dst_file, *src_file);
			if (dst_file == NULL)
				return (false);
		}
		if (ft_strncmp(dst_file, src_file, 1) != 0)
			return (false);
		if (*dst_file)
			++dst_file;
		if (*src_file)
			++src_file;
	}
	return (true);
}

static void	skip_dot_directory(DIR *dirp)
{
	readdir(dirp);
	readdir(dirp);
}

void	expand_wildcard(t_token *token)
{
	DIR				*dirp;
	struct dirent	*dp;
	char			*new_token_value;

	dirp = opendir(".");
	new_token_value = ft_strdup("");
	skip_dot_directory(dirp);
	while (true)
	{
		dp = readdir(dirp);
		if (dp == NULL)
			break ;
		if (token->value[0] != '.' && dp->d_name[0] == '.')
			continue ;
		if (is_matchable_asterisk(dp->d_name, token->value) == true)
		{
			new_token_value = ft_strjoin(new_token_value, dp->d_name);
			new_token_value = ft_charjoin(new_token_value, ' ');
		}
	}
	free(token->value);
	if (ft_strlen(new_token_value) > 0)
		new_token_value[ft_strlen(new_token_value) - 1] = 0;
	token->value = new_token_value;
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

void	expand_dollar(t_token *token)
{
	char	*command;
	char	*quote_content;
	char	*expanded_command;

	expanded_command = ft_strdup("");
	command = token->value;
	while (*command)
	{
		if (*command == '\'')
		{
			quote_content = read_quote_content(&command, '\'');
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		else if (*command == '"')
		{
			quote_content = read_quote_content(&command, '\"');
			// expand_content(quote_content);
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		else
		{
			quote_content = read_not_quote_content(&command);
			// expand_content(quote_content);
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		++command;
	}
}
