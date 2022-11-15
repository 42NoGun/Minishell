/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:45:35 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/15 17:00:43 by jiyunpar         ###   ########.fr       */
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
	test_read_wrapped_content();
	printf("success read_quote_content() test!\n");
	test_tokenize();
	printf("success tokenize() test!\n");
	test_parser();
	printf("success parser() test!\n");
	test_check_syntax_error();
	printf("success test_check_syntax_error() test!\n");
	printf("success test!\n");
	return (0);
}
