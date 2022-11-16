/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_is_matchable_asterisk.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:17:41 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/16 14:15:23 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	test_is_matchable_asterisk(void)
{
	ft_assert(is_matchable_asterisk("Makefile", "M*"),
		true, "is_matchable_asterisk, 5");
	ft_assert(is_matchable_asterisk("Makefile", "*M*"),
		true, "is_matchable_asterisk, 6");
	ft_assert(is_matchable_asterisk("Makefile", "*******M*******"),
		true, "is_matchable_asterisk, 7");
	ft_assert(is_matchable_asterisk("m", "M"),
		false, "is_matchable_asterisk, 8");
	ft_assert(is_matchable_asterisk("Makefile", "*"),
		true, "is_matchable_asterisk, 9");
	ft_assert(is_matchable_asterisk("makpfile", "*ee"),
		false, "is_matchable_asterisk, 10");
	ft_assert(is_matchable_asterisk("Make", "Makefile*"),
		false, "is_matchable_asterisk, 11");
	ft_assert(is_matchable_asterisk("Makefile", "*****"),
		true, "is_matchable_asterisk, 12");
	ft_assert(is_matchable_asterisk("Make*file", "*****"),
		true, "is_matchable_asterisk, 13");
	ft_assert(is_matchable_asterisk("Makefile", "*M*a*k*e*f*i*l*e*"),
		true, "is_matchable_asterisk, 14");
	ft_assert(is_matchable_asterisk("Makefile", "M*k*i*e"),
		true, "is_matchable_asterisk, 15");
	ft_assert(is_matchable_asterisk("Make", "*M"),
		false, "is_matchable_asterisk, 16");
	ft_assert(is_matchable_asterisk("allcheck", "*.c"),
		false, "is_matchable_asterisk, 41");
}
