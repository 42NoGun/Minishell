/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:52 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/12 15:42:02 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// cd /Home/junji/Desktop
// cd ../d
// cd ~ <- 절대 경로
// cd <- ..???
// int chdir( const char *dirname );
//dirname : 변경할 디렉토리의 경로
//반환값 : 정상 일 때 0, 에러 시 -1

#include "minishell.h"

void	b_cd(char **command, t_list *env_list)
{
	char	*home;
	int		i;

	i = 0;
	while (command[i])
		++i;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return ;
	}
	if (command[1] == NULL || ft_strcmp(command[1], "~") == 0)
	{
		home = ft_getenv(env_list, "HOME");
		if (home == NULL)
			return ;
		chdir(home);
	}
	chdir(command[1]);
}
