/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 14:05:55 by jiyunpar         ###   ########.fr       */
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
// ls *(a, b, c) d e
// 
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
			new_token_value = ft_strjoin_left_free(new_token_value, dp->d_name);
			new_token_value = ft_charjoin(new_token_value, ' ');
		}
	}
	closedir(dirp);
	if (ft_strlen(new_token_value) > 0)
	{
		free(token->value);
		token->value = new_token_value;
		new_token_value[ft_strlen(new_token_value) - 1] = 0;
		return ;
	}
	free(new_token_value);
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
// "hello $? hello $PATH"
// "hello 127 hello /opt/333"
// $? dkjdfk
// $?$
// $PATH$sdfsdf
// $?abc
		// echo "hello $PATH"
		// len = 6
		// extra_content = "hello2 $PATH |||| hello $PATH"
		// expanded_content 
		/*
		- 달러 전까지 길이를 잰다.
		- substr
		- 달러가 나왔으면 확장 후 substr
		1. $가 아니라면 qoute_content에 붙임(substr);
		2. $가 나오면
			1) 달러 다음 문자가 ?인지
			2) 달러 다음이 또 딸러인지
			3) 달러 다음이 공백인지
		3. substr 
			1) ? : exit_staus(itoa)
			2) els : getenv() -> parsing
		*/

char	*expand_content(char *content, t_list *env_list)
{
	char	*env_content;
	char	*expanded_content;
	char	*extra_content;
	char	*converted_env_content;
	char	*content_init_pos;
	int		before_dollar_len;
	int		env_content_len;

	content_init_pos = content;
	expanded_content = ft_strdup("");
	while (*content)
	{
		before_dollar_len = 0;
		while (*content && *content != '$')
		{
			++content;
			++before_dollar_len;
		}
		extra_content = ft_substr(content - before_dollar_len,
				0, before_dollar_len);
		expanded_content = ft_strjoin(expanded_content, extra_content);
		if (!*content)
			break ;
		++content;
		env_content_len = 0;
		while (*content && *content != ' ' && (ft_isalnum(*content) || *content == '?'))
		{
			++content;
			++env_content_len;
		}
		env_content = ft_substr(content - env_content_len, 0, env_content_len);
		if (ft_strcmp(env_content, "?") == 0)
		{
			converted_env_content = ft_itoa(WEXITSTATUS(g_exit_status));
			expanded_content = ft_strjoin(expanded_content,
					converted_env_content);
		}
		else
		{
			converted_env_content = ft_getenv(env_list, env_content);
			if (converted_env_content)
				expanded_content = ft_strjoin_left_free(expanded_content,
						converted_env_content);
		}
		free(env_content);
	}
	free(content_init_pos);
	return (expanded_content);
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
		if (*command == '\'')
		{
			quote_content = read_quote_content(&command, '\'');
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		else if (*command == '"')
		{
			quote_content = read_quote_content(&command, '\"');
			quote_content = expand_content(quote_content, env_list);
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		else
		{
			quote_content = read_not_quote_content(&command);
			quote_content = expand_content(quote_content, env_list);
			expanded_command = ft_strjoin(expanded_command, quote_content);
		}
		++command;
	}
	free(token->value);
	token->value = expanded_command;
}
