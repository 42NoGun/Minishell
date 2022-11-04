/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:46:01 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/04 15:32:25 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_is_even_quote(void)
{
	const char	*str = "(ls | \"ls | ls\")";
	const char	*str2 = "(ls | ls | ls\")";
	const char	*str3 = "(ls | ls\' | ls";

	ft_assert(is_even_quote(str), true, "check_pair line: 17 fail");		
	ft_assert(is_even_quote(str2), false, "check_pair line: 18 fail");		
	ft_assert(is_even_quote(str3), true, "check_pair line: 19 fail");		
}