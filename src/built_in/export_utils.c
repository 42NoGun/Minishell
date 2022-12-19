/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/17 20:06:02 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/18 20:00:30 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_swap(char **a, char **b)
{
	char	*temp;

	temp = *a;
	*a = *b;
	*b = temp;
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
		ft_putendl_fd(env_argument[index], 1);
	}
}
