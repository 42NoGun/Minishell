/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_pair_quote.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:10:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/18 10:07:16 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_is_pair_quote(void)
{
	const char	*str = "\"\'\"\'";
	const char	*str2 = "\'\"\'\"";
	const char	*str3 = "\"\'\'\'\"\'";
	const char	*str4 = "\"\'\'\'\"";

	ft_assert(is_pair_quote(str), false, "is_pair_quote line: 17 fail");
	ft_assert(is_pair_quote(str2), false, "is_pair_quote line: 18 fail");
	ft_assert(is_pair_quote(str3), false, "is_pair_quote line: 19 fail");
	ft_assert(is_pair_quote(str4), true, "is_pair_quote line: 20 fail");
}