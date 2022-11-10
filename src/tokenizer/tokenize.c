/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 17:06:04 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 17:16:25 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "linked_list.h"

bool	is_quote(char c)
{
	if (c == SINGLE_QUOTE || c == DOUBLE_QUOTE)
		return (true);
	return (false);
}

bool	is_operator(char c)
{
	if (c == PIPE || c == IN_REDIR || c == OUT_REDIR)
		return (true);
	return (false);
}

void	tokenize(const char *line, t_list *cmd_list)
{
	char	*prev_str;

	prev_str = ft_strdup("");
	while (*line)
	{
		if (ft_strlen(prev_str) == 1
			&& is_operator(*prev_str) == is_operator(*(line))
			&& !is_quote(*line))
		{
			ft_charjoin(prev_str, *line);
		}
		else if (ft_strlen(prev_str) == 1
			&& is_operator(*prev_str)
			&& !is_operator(*line))
		{
			put_token_in_list(prev_str, cmd_list);
			prev_str = ft_chardup(*line);
		}
		else if (is_quote(*line))
		{
			ft_strjoin(prev_str, read_quote_content());
			// ft_strjoin이 끝난 시점에 포인터는 quote가리킴
		}
		// else if (is_bracket(*line))
		// {
		// 	//read_bracket_content();
		// 	put_token_in_list(prev_str, cmd_list);
		// }
		// else if (is_dollar(*line))
		// {
		// 	//ft_strjoin(prev_str, expand()); // 공백이거나 오퍼레이터 까지 읽어서 확장
		// }
		else if (!is_quote(*line) && is_operator(*line))
		{
			put_token_in_list(prev_str, cmd_list);
			prev_str = ft_chardup(*line);
		}
		else if (*line == ' ')
		{
			put_token_in_list(prev_str, cmd_list);
			while (*line && *line == ' ')
			{
				++line;
			}
			if (!*line)
				break ;
			if (!is_operator(*line))
				continue ;
			prev_str = ft_chardup(*line); // "a" 'b' // prev_str에 '들어감
		}
		else
			ft_charjoin(prev_str, *line);
		++line;
	}
	if (prev_str)
		put_token_in_list(prev_str, cmd_list);
}
