/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:45:35 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/16 11:54:34 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

int	main(void)
{
	printf("\n=======================================================\n");
	test_is_even_quote();	
	printf("success is_even_quote() test!\n");
	printf("\n=======================================================\n");
	test_is_pair_quote();
	printf("success is_pair_quote() test!\n");
	printf("\n=======================================================\n");
	test_is_pair_bracket();
	printf("success is_eve() test!\n");
	printf("\n=======================================================\n");
	test_is_correct_pair();
	printf("success is_correct_pair() test!\n");
	printf("\n=======================================================\n");
	test_read_wrapped_content();
	printf("success read_quote_content() test!\n");
	printf("\n=======================================================\n");
	test_tokenize();
	printf("success tokenize() test!\n");
	printf("\n=======================================================\n");
	test_parser();
	printf("success parser() test!\n");
	printf("\n=======================================================\n");
	test_check_syntax_error();
	printf("success test_check_syntax_error() test!\n");
	printf("\n=======================================================\n");
	test_is_matchable_asterisk();
	printf("success test_is_matchable_asterisk() test!\n");
	printf("\n=======================================================\n");
	printf("success test!\n");
	return (0);
}
