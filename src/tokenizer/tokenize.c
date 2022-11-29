/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:06:04 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/29 10:03:46 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "linked_list.h"

bool	is_bracket(char c)
{
	if (c == OPEN_BRACKET)
		return (true);
	return (false);
}

bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == PIPE || c == IN_REDIR || c == OUT_REDIR || c == AND)
		return (true);
	return (false);
}

bool	is_space(char c)
{
	if (c == ' ')
		return (true);
	return (false);
}

void	tokenize(char *line, t_list *cmd_list)
{
	char	*prev_str;

	prev_str = ft_strdup("");
	while (*line)
	{
		if (ft_strlen(prev_str) == 1
			&& is_operator(*prev_str) && is_operator(*line)
			&& !is_quote(*line))
		{
			prev_str = ft_charjoin(prev_str, *line);
			put_token_in_list(prev_str, cmd_list);
			prev_str = ft_strdup("");
		}
		else if (ft_strlen(prev_str) == 1
			&& is_operator(*prev_str)
			&& !is_operator(*line) && !is_space(*line))
		{
			put_token_in_list(prev_str, cmd_list);
			if (*line == OPEN_BRACKET)
			{
				prev_str = ft_strdup("");
				continue ;
			}
			prev_str = ft_chardup(*line);
		}
		else if (is_quote(*line))
		{
			if (*line == '"')
				prev_str = ft_strjoin(prev_str, read_quote_content(&line, '"'));
			if (*line == '\'')
				prev_str = ft_strjoin(prev_str,
						read_quote_content(&line, '\''));
		}
		else if (is_bracket(*line))
		{
			prev_str = ft_strjoin(prev_str, read_group_content(&line));
			put_token_in_list(prev_str, cmd_list);
			prev_str = ft_strdup("");
		}
		else if (!is_quote(*line) && is_operator(*line))
		{
			put_token_in_list(prev_str, cmd_list);
			prev_str = ft_chardup(*line);
		}
		else if (is_space(*line))
		{
			put_token_in_list(prev_str, cmd_list);
			while (*line && is_space(*line))
			{
				++line;
			}
			if (!*line)
				break ;
			if (!is_operator(*line))
			{
				prev_str = ft_strdup("");
				continue ;
			}
			prev_str = ft_chardup(*line);
		}
		else
			prev_str = ft_charjoin(prev_str, *line);
		++line;
	}
	if (prev_str)
		put_token_in_list(prev_str, cmd_list);
}
