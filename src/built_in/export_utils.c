/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:06:02 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/18 14:55:02 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_valid_key(char *key)
{
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (false);
	++key;
	while (*key)
	{
		if (!ft_isalnum(*key) && *key != '_')
			return (false);
		++key;
	}
	return (true);
}

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// Author: hanbkim
static void	print_export_value(char	*arg)
{
	int	i;

	i = 0;
	if (ft_strchr(arg, '=') != NULL)
	{
		while (arg[i] != '=')
			++i;
		_write(1, arg, i + 1);
		_write(1, "\"", 1);
		_write(1, arg + i + 1, ft_strlen(arg) - i - 1);
		_write(1, "\"\n", 2);
	}
	else
	{
		ft_putendl_fd(arg, 1);
	}
}

void	print_export(t_list *env_list)
{
	char	**env_argument;
	int		index;
	int		jndex;

	env_argument = list_to_2d_array(env_list);
	index = 0;
	while (++index < env_list->len - 1)
	{
		jndex = 0;
		while (++jndex < (env_list->len - index))
		{
			if (ft_strcmp(env_argument[jndex], env_argument[jndex + 1]) > 0)
				ft_swap(&env_argument[jndex], &env_argument[jndex + 1]);
		}
	}
	index = -1;
	while (++index < env_list->len)
	{
		ft_putstr_fd("declare -x ", 1);
		print_export_value(env_argument[index]);
	}
	free(env_argument);
}
