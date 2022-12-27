/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils1_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 10:57:18 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/27 22:48:33 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "minishell_bonus.h"

static bool	is_ordered_heredoc(char **file_path, char *sequence)
{
	DIR				*dirp;
	struct dirent	*dp;

	dirp = opendir("/tmp/heredoc/");
	dp = readdir(dirp);
	dp = readdir(dirp);
	while (true)
	{
		dp = readdir(dirp);
		if (dp == NULL)
		{
			closedir(dirp);
			return (false);
		}
		if (ft_strcmp(sequence, dp->d_name) == 0)
		{
			*file_path = ft_strdup(dp->d_name);
			closedir(dirp);
			return (true);
		}
	}
}

char	*get_heredoc_file_path(void)
{
	char			*file_path;
	char			*sequence;
	const char		*prefix = "/tmp/heredoc/";
	int				i;

	i = 0;
	while (1)
	{
		sequence = ft_itoa(i);
		if (is_ordered_heredoc(&file_path, sequence))
		{
			free(sequence);
			break ;
		}
		free(sequence);
		++i;
	}
	file_path = ft_strjoin_right_free(prefix, file_path);
	return (file_path);
}
