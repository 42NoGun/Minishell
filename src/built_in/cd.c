/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:49:52 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/27 10:33:58 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_path(char *command, t_list *env_list)
{
	char	*path;

	if (command == NULL || ft_strcmp(command, "~") == 0)
	{
		path = ft_getenv(env_list, "HOME");
		if (path == NULL)
		{
			ft_putendl_fd("cd: HOME not set", 2);
			return (NULL);
		}
		return (ft_strdup(path));
	}
	else if (ft_strncmp(command, "~", 1) == 0)
	{
		path = ft_strjoin_left_free(ft_strdup(ft_getenv(env_list, "HOME")),
				command + 1);
	}
	else
		path = ft_strdup(command);
	return (path);
}

static char	*set_pwd(void)
{
	char	*pwd;
	char	buf[256];

	getcwd(buf, 256);
	pwd = ft_strjoin_no_free("PWD=", buf);
	return (pwd);
}

static char	*set_oldpwd(t_list *env_list)
{
	char	*old_pwd;
	char	*env;

	env = ft_getenv(env_list, "PWD");
	if (env == NULL)
		return (NULL);
	old_pwd = ft_strjoin_no_free("OLDPWD=", env);
	return (old_pwd);
}

static bool	has_cd_many_argument(char **command)
{
	int		i;

	i = 0;
	while (command[i])
		++i;
	if (i > 2)
	{
		ft_putstr_fd("cd: too many arguments\n", 2);
		return (true);
	}
	return (false);
}

int	b_cd(char **command, t_list *env_list)
{
	char	*path;
	char	*old_pwd;
	char	*pwd;
	int		ret;

	if (has_cd_many_argument(command) == true)
		return (1);
	path = get_path(command[1], env_list);
	if (path == NULL)
		return (1);
	old_pwd = set_oldpwd(env_list);
	if (old_pwd != NULL)
	{
		ft_setenv(env_list, "OLDPWD", old_pwd);
		free(old_pwd);
	}
	ret = _chdir(path);
	pwd = set_pwd();
	if (pwd != NULL)
	{
		ft_setenv(env_list, "PWD", pwd);
		free(pwd);
	}
	free(path);
	return (ret);
}
