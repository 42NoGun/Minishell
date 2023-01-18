/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_content.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 17:42:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/23 15:18:54 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// read_quote_content
// - make str with quoted characters
// 1. ++line
// 2. ft_strdup("")
// 3. ft_charjoin() until next quote

char	*read_quote_content(char **line, char quote)
{
	char	*quote_content;
	size_t	len;

	len = ft_strchr((*line + 1), quote) - *line;
	quote_content = ft_substr(*line, 0, len + 1);
	*line += len;
	return (quote_content);
}

char	*read_inside_quote_content(char **line, char quote)
{
	char	*quote_content;
	size_t	len;

	len = ft_strchr((*line + 1), quote) - *line;
	if (ft_strchr((*line + 1), quote) == NULL)
		return (ft_strdup(*line));
	quote_content = ft_substr(*line + 1, 0, len - 1);
	*line += len;
	return (quote_content);
}

char	*read_group_content(char **line)
{
	char	*grouped_content;
	char	*init_pos;
	size_t	len;
	int		bracket_count;

	init_pos = *line;
	bracket_count = 0;
	len = 0;
	while (**line)
	{
		if (**line == '(')
			++bracket_count;
		else if (**line == ')')
		{
			--bracket_count;
			if (bracket_count == 0)
			{
				len = *line - init_pos;
				break ;
			}
		}
		++(*line);
	}
	grouped_content = ft_substr(init_pos, 0, len + 1);
	return (grouped_content);
}
