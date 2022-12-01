/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_main.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:45:35 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/01 16:42:50 by jiyunpar         ###   ########.fr       */
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
	printf("success is_pair_bracket() test!\n");
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
	test_expand_wildcard();
	printf("success test_expand_wildcard() test!\n");
	printf("\n=======================================================\n");
	test_expand_dollar();
	printf("success test_expand_dollar() test!\n");
	printf("\n=======================================================\n");
	test_convert_tree_to_exec_list();
	printf("success test_convert_tree_to_exec_list() test!\n");
	printf("\n=======================================================\n");
	test_refined_field();
	printf("success test_refined_field() test!\n");
	return (0);
}
