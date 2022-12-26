/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:49:39 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/25 20:51:15 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>

static char	*get_limiter(char *value)
{
	int	end;

	end = 0;
	while (value[end])
	{
		if (!ft_isalnum(value[end]))
			break ;
		++end;
	}
	return (ft_substr(value, 0, end));
}

void	skip_quote_content(char **value, char quote)
{
	size_t	len;

	len = ft_strchr((*value + 1), quote) - *value;
	*value += len;
}

void	push_back_limiter(t_node *node, t_list *limiter_list)
{
	char	*value;

	value = ((t_token *)node->content)->value;
	push_back(limiter_list, make_node(ft_strdup(value)));
}

void	push_back_subshell_limiter(char *value, t_list *limiter_list)
{
	char	*limiter;

	++value;
	while (*value && *value == ' ')
		++value;
	limiter = get_limiter(value);
	push_back(limiter_list, make_node(limiter));
}
