/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_pair.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 13:46:01 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/04 14:45:06 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_is_correct_pair(void)
{
	const char	*str = "(ls | \"ls | ls\")";

	ft_assert(is_even_quote(str), true, "check_pair line: 17 fail");		
}