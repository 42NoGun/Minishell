/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:09 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/16 13:16:44 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

#include "libft.h"

void	ft_swap(char **a, char **b)
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
	index = 0;
	while (++index < env_list->len)
	{
		ft_putstr_fd("declare -x ", 1);
		ft_putendl_fd(env_argument[index], 1);
	}
}
// export [key]=[value]
// 예외 -> key의 시작 문자는 숫자면 안됨
	// 예외이면 exit status 1
// 동일한 key값만 오면 update 안됨
// 동일한 key값 + = 이면 (a=) =으로 업데이트됨
// key에 =이 들어올 수 없다!!!

static char	*get_key(char *command, char *value)
{
	char	*key;

	key = ft_substr(command, 0, value - command);
	if (!key)
		ft_terminate("get_key, ft_substr");
	return (key);
}

static char	*get_value(char *command)
{
	char	*value;

	value = ft_strchr(command, '=');
	return (value);
}
//env_list " "
//env_list를

// PATH같은 경우에는 env_list에 " "이 없음
// export a="b"; 같은 경우 env_list 에 " "이 있음

//	1. export 출력 : 정렬하고 출력, " "넣어서 출력
//  2. env 출력 : 따옴표를 제거하고 출력 

// 1. 처음부터 " " 다넣고함

//
// 키만 있는 경우에는 env는 출력 안하고, export는 키만 출력  
// export a=abc
// command[i] : a=abc --> a="abc"
// command[i] : a="abc"
// command[i] : a
void	b_export(char **command, t_list *env_list)
{
	int		i;
	char 	*key;
	char 	*value;
	char 	*quoted_env;

	if (command[1] == NULL)
	{
		print_export(env_list);
		return ;
	}
	i = 1;
	while (command[i])
	{
		if (ft_isdigit(command[i][0]))
		{
			perror("export: not an identifier");
			++i;
			continue ;
		}
		value = get_value(command[i]);// =abc
		key = get_key(command[i], value);// a 
		if (ft_getenv(env_list, key)) // 키가 있음
		{
			if (value) // =abc
			{
				ft_setenv(env_list, key, value, command[i]); // 해당 위치 node content의 값을 갱신함
			}
		}
		else // 키가 없어
		{
			quoted_env = get_quoted_env(command[i]);
			push_back(env_list, make_node(quoted_env));
		}
		free(key);
		++i;
	}
}
