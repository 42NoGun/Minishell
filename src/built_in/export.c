/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 15:50:09 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/12 17:41:39 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "minishell.h"

//#include "libft.h"

// void	ft_swap(char **a, char **b)
// {
// 	char	*temp;

// 	temp = *a;
// 	*a = *b;
// 	*b = temp;
// }

// int	ft_strcmp(const char *s1, const char *s2)
// {
// 	while (*s1 && (*s1 == *s2))
// 	{
// 		++s1;
// 		++s2;
// 	}
// 	return (*s1 - *s2);
// }

// int	ft_strlen(const char *str)
// {
// 	int	len;

// 	len = 0;
// 	while (*str)
// 	{
// 		++len;
// 		++str;
// 	}
// 	return (len);
// }

// void	ft_putstr(const char *str)
// {
// 	while (*str)
// 		write(1, str++, 1);
// }

// int	main(int argc, char *argv[])
// {
// 	int	index;
// 	int	jndex;

// 	index = 0;
// 	while (++index < argc - 1)
// 	{
// 		jndex = 0;
// 		while (++jndex < (argc - index))
// 		{
// 			if (ft_strcmp(argv[jndex], argv[jndex + 1]) > 0)
// 				ft_swap(&argv[jndex], &argv[jndex + 1]);
// 		}
// 	}
// 	index = 0;
// 	while (++index < argc)
// 	{
// 		ft_putstr(argv[index]);
// 		write(1, "\n", 1);
// 	}
// 	return (0);
// }

void	print_env(t_list *env_list)
{
	//printf("declare -x %s=\"%s\"", key, value);
	// 1. sort
	// 2. print
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

void	b_export(char **command, t_list *env_list)
{
	int		i;
	char 	*key;
	char 	*value;

	if (command[1] == NULL)
	{
		return ;
		// print_env();
		// return ;
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
		value = get_value(command[i]);
		key = get_key(command[i], value);
		if (ft_getenv(env_list, key)) // 키가 있음
		{
			if (value)
			{
				ft_setenv(env_list, key, command[i]); // 해당 위치 node content의 값을 갱신함
			}
		}
		else // 키가 없어
		{
			push_back(env_list, make_node(command[i]));
		}
		free(key);
		++i;
	}
}
