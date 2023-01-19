/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 11:01:48 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/19 21:25:08 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "minishell_bonus.h"

static bool	open_error(int fd, bool parent)
{
	if (fd == -1 && !parent)
		ft_terminate("redirection, open");
	if (fd == -1 && parent)
	{
		ft_putendl_fd(strerror(errno), 2);
		return (true);
	}
	return (false);
}

static bool	redirect_file_stream(char *file,
	int open_flag, int dup_fd, bool parent)
{
	int	fd;

	fd = open(file, open_flag, 0666);
	if (open_error(fd, parent))
		return (true);
	_dup2(fd, dup_fd);
	_close(fd);
	return (false);
}

bool	heredoc(char **redirections, int std_in, bool parent)
{
	int		i;
	char	*file_path;

	i = 0;
	while (redirections[i])
	{
		if (ft_strcmp(redirections[i], "<<") == 0)
		{
			_dup2(std_in, 0);
			file_path = get_heredoc_file_path();
			if (redirect_file_stream(file_path, O_RDONLY, 0, parent) == true)
				return (false);
			unlink(file_path);
			free(file_path);
		}
		i += 2;
	}
	if (!parent)
		_close(std_in);
	return (true);
}

bool	redirection(char **redirections, bool parent)
{
	int		i;
	bool	open_error;

	i = 0;
	open_error = false;
	while (redirections[i])
	{
		if (ft_strcmp(redirections[i], ">>") == 0)
			open_error = redirect_file_stream(redirections[i + 1],
					O_CREAT | O_WRONLY | O_APPEND, 1, parent);
		if (ft_strcmp(redirections[i], ">") == 0)
			open_error = redirect_file_stream(redirections[i + 1],
					O_CREAT | O_TRUNC | O_WRONLY, 1, parent);
		if (ft_strcmp(redirections[i], "<") == 0)
			open_error = redirect_file_stream(
					redirections[i + 1], parent, O_RDONLY, parent);
		if (open_error)
			return (false);
		i += 2;
	}
	return (true);
}
