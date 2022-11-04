/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:15:05 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/04 15:23:26 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_even_quote(const char *line)
{
	int	single_quote_count;	
	int	double_quote_count;	
	
	single_quote_count = 0;
	double_quote_count = 0;
	while (*line)
	{
		if (*line == SINGLE_QUOTE)
			++single_quote_count;
		if (*line == DOUBLE_QUOTE)
			++double_quote_count;
		++line;
	}
	return (single_quote_count % 2 == 0 && \
			double_quote_count % 2 == 0);
}

bool	is_pair_bracket(const char *line)
{
	int		count;
	// bool	is_in_quote;

	count = 0;
	// is_in_quote = false;
	while (*line)
	{
		if (*line == DOUBLE_QUOTE)
		{
			++line;
			while (*line != DOUBLE_QUOTE)
				++line;
		}
		if (*line == SINGLE_QUOTE)
		{
			++line;
			while (*line != SINGLE_QUOTE)
				++line;
		}
		if (*line == OPEN_BRACKET)
			count += 1;
		if (*line == CLOSE_BRACKET)
			count -= 1;
		++line;
	}
	if (count != 0)
		return (false);
	return (true);
}

bool	is_correct_pair(const char *line)
{
	if (is_even_quote(line) == false)
	{
		return (false);
	}
	// if (is_pair_quote(line) == false)
	// {
	// }
	// if (is_pair_bracket(line) == false)
	// {
	//}
	return (true);
}
