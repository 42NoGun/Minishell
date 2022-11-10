/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:45:35 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 17:16:44 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(void)
{
	test_is_even_quote();
	printf("success is_even_quote() test!\n");
	test_is_pair_quote();
	printf("success is_pair_quote() test!\n");
	test_is_pair_bracket();
	printf("success is_pair_bracket() test!\n");
	test_is_correct_pair();
	printf("success is_correct_pair() test!\n");
	test_read_quote_content();
	printf("success read_quote_content() test!\n");
	printf("success test!\n");
	return (0);
}
