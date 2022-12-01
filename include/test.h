/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/04 14:46:46 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/01 16:42:13 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEST_H
# define TEST_H
# include "minishell.h"

void	test_is_even_quote(void);
void	test_is_pair_quote(void);
void	test_is_pair_bracket(void);
void	test_is_correct_pair(void);
void	test_read_wrapped_content(void);
void	test_tokenize(void);
void	test_parser(void);
void	test_check_syntax_error(void);
void	test_is_matchable_asterisk(void);
void	test_expand_wildcard(void);
void	test_expand_dollar(void);
void	test_check_redirection_error(void);
void	test_convert_tree_to_exec_list(void);
void	test_refined_field(void);

#endif