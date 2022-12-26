/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pair_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 10:54:33 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/26 10:35:48 by junji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

static bool	is_pair_quote(const char *line)
{
	int	single_quote_count;
	int	double_quote_count;

	single_quote_count = 0;
	double_quote_count = 0;
	while (*line)
	{
		single_quote_count += check_pair_quote(&line, '\'');
		double_quote_count += check_pair_quote(&line, '"');
		if (!*line)
			break ;
		++line;
	}
	if (single_quote_count == 0 && double_quote_count == 0)
		return (true);
	return (false);
}

static bool	is_pair_bracket(const char *line)
{
	int	bracket_count;

	bracket_count = 0;
	while (*line)
	{
		check_pair_quote(&line, '\'');
		check_pair_quote(&line, '"');
		if (*line == '(')
			++bracket_count;
		else if (*line == ')')
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
	if (is_pair_quote(line) == false)
	{
		ft_putstr_fd("minishell : pair error\n", 2);
		g_exit_status = 2 << 8;
		return (false);
	}
	if (is_pair_bracket(line) == false)
	{
		ft_putstr_fd("minishell : pair error\n", 2);
		g_exit_status = 2 << 8;
		return (false);
	}
	return (true);
}
