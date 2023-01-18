/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:09 by cheseo            #+#    #+#             */
/*   Updated: 2023/01/18 14:56:09 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	export_with_no_arguments(char **command, t_list *env_list)
{
	if (command[1] == NULL)
	{
		print_export(env_list);
		return ;
	}
}

static void	update_env(char *command, char *key, char *value, t_list *env_list)
{
	if (value)
		ft_setenv(env_list, key, command);
}

static void	push_env(char *command, t_list *env_list)
{
	push_back(env_list, make_node(ft_strdup(command)));
}

static void	export_with_arguments(char **command, t_list *env_list, int *ret)
{
	int		i;
	char	*value;
	char	*key;

	i = 1;
	while (command[i])
	{
		value = get_value_export(command[i]);
		key = get_key(command[i], value);
		if (!is_valid_key(key))
		{
			ft_putendl_fd("export: not an identifier", 2);
			*ret = 1;
			++i;
			continue ;
		}
		if (ft_getenv(env_list, key))
			update_env(command[i], key, value, env_list);
		else
			push_env(command[i], env_list);
		free(key);
		++i;
	}
}

// export
// - env_list is doubly linked list
// - each node has string value as below
// ex) USER=jiyunpar -> unquoted key & unquoted value
// with no arguments
// 1. change linked list to 2d array
// 2. sort 2d array in ascending order
// 3. print with quote 
// with arguments
// 1. pushback variable to linked list
int	b_export(char **command, t_list *env_list)
{
	int	ret;

	ret = 0;
	export_with_no_arguments(command, env_list);
	export_with_arguments(command, env_list, &ret);
	return (ret);
}
