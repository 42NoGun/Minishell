/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 15:01:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/28 12:03:55 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <sys/stat.h>

static bool	put_correct_path(char *path, char **command, struct stat *buf)
{
	char	*command_with_path;

	command_with_path = ft_strjoin_left_free(path, "/");
	command_with_path = ft_strjoin_left_free(command_with_path, *command);
	if (lstat(command_with_path, buf) == 0)
	{
		free(*command);
		*command = command_with_path;
		return (true);
	}
	return (false);
}

static void	check_file_permission(struct stat *buf)
{
	if ((buf->st_mode & S_IXUSR) == 0)
	{
		ft_putendl_fd("Permission denied", 2);
		exit(126);
	}
	if (S_ISDIR(buf->st_mode))
	{
		ft_putendl_fd("Is a directory", 2);
		exit(126);
	}
}

static void	check_have_path(char *path)
{
	if (path == NULL)
	{
		ft_putendl_fd("No such file or directory", 2);
		exit(127);
	}
}

void	find_path(char **command, t_list *env_list)
{
	char		**path_list;
	int			i;
	struct stat	buf;

	if (ft_strchr(*command, '/') != NULL)
	{
		if (lstat(*command, &buf) != 0)
		{
			*command = NULL;
			return ;
		}
		check_file_permission(&buf);
		return ;
	}
	path_list = ft_split(ft_getenv(env_list, "PATH"), ':');
	check_have_path(path_list[0]);
	i = 0;
	while (path_list[i])
	{
		if (put_correct_path(path_list[i], command, &buf))
			return ;
		++i;
	}
	*command = NULL;
}
