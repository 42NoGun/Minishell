/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_correct_pair.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 14:11:35 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/07 14:17:10 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_is_correct_pair(void)
{
	const char	*str = "(ls | ls && (ls && ls | ls)) || ls >> filepath";
	const char	*str2 = "(ls | \"ls && (ls && ls | ls))\"";
	const char	*str3 = "(ls | \"ls && (ls && ls | ls)\")";

	ft_assert(is_correct_pair(str), true, "is_correct_pair line: 17 fail");
	ft_assert(is_correct_pair(str2), false, "is_correct_pair line: 18 fail");
	ft_assert(is_correct_pair(str3), true, "is_correct_pair line: 19 fail");
}