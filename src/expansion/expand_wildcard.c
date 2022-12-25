/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_wildcard.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/25 20:46:01 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "minishell.h"

static bool	is_matchable_asterisk(char *dst_file, char *src_file)
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

bool	can_change_new_token_value(char *new_token_value, t_token **token)
{
	if (ft_strlen(new_token_value) > 0)
	{
		free((*token)->value);
		(*token)->value = new_token_value;
		new_token_value[ft_strlen(new_token_value) - 1] = 0;
		return (true);
	}
	return (false);
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
	if (can_change_new_token_value(new_token_value, &token))
		return ;
	free(new_token_value);
}
