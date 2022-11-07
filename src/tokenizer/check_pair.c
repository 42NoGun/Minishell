/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pair.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 11:15:05 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/07 11:37:28by jiyunpar         ###   ########.fr       */
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
	if (single_quote_count % 2 == 0 && \
			double_quote_count % 2 == 0)
		return (true);
	return (false);
}

static int	check_pair_quote(const char **line, char quote)
{
	int	quote_count;

	quote_count = 0;
	if (**line == quote)
	{
		++(*line);
		quote_count += 1;
		while (**line && **line != quote)
		{
			++(*line);
		}
		if (**line == quote)
			quote_count -= 1;
	}
	return (quote_count);
}

bool	is_pair_quote(const char *line)
{
	int	single_quote_count;
	int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	while (*line)
	{
		single_quote_count += check_pair_quote(&line, SINGLE_QUOTE);
		double_quote_count += check_pair_quote(&line, DOUBLE_QUOTE);
		++line;
	}
	if (single_quote_count == 0 && double_quote_count == 0)
		return (true);
	return (false);
}

bool	is_pair_bracket(const char *line)
{
	int	bracket_count;

	bracket_count = 0;

	while (*line)
	{
		check_pair_quote(&line, SINGLE_QUOTE);
		check_pair_quote(&line, DOUBLE_QUOTE);
		if (*line == OPEN_BRACKET)
			++bracket_count;
		else if (*line == CLOSE_BRACKET)
		{
			if (bracket_count == 0)
				return (false);
			--bracket_count;
		}
		++line;
	}
	if (bracket_count == 0)
		return (true);
	return (false);
}

bool	is_correct_pair(const char *line)
{
	if (is_even_quote(line) == false)
	{
		return (false);
	}
	if (is_pair_quote(line) == false)
	{
		return (false);
	}
	if (is_pair_bracket(line) == false)
	{
		return (false);
	}
	return (true);
}
