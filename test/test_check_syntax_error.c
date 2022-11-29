/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_check_syntax_error.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 09:07:40 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/29 15:41:57 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.h"

static void	_case(const char *str, bool flag, char *error_message)
{
	t_list	*cmd_list;
	t_tree	*cmd_tree;

	cmd_list = init_list();
	cmd_tree = init_tree();
	tokenize((char *)str, cmd_list);
	parser(cmd_tree, cmd_list);
	ft_assert(check_syntax_error(cmd_tree), flag, error_message);
	free_list(cmd_list);
	free_tree(cmd_tree);
}

static void	case_one(void)
{
	const char	*str1 = "ls |";
	const char	*str2 = "ls ||||||| ls";
	const char	*str3 = "echo | grep hello | ls &&";
	const char	*str4 = "||";
	const char	*str5 = "ls | ls | ls || ls | ls | ls |";

	printf("\n=============case 1 - 1====================\n");
	_case(str1, false, "case_one, 32");
	printf("\n=============case 1 - 2====================\n");
	_case(str2, false, "case_one, 33");
	printf("\n=============case 1 - 3====================\n");
	_case(str3, false, "case_one, 34");
	printf("\n=============case 1 - 4====================\n");
	_case(str4, false, "case_one 35");
	printf("\n=============case 1 - 5====================\n");
	_case(str5, false, "case_one, 36");
}

static void	case_two(void)
{
	const char	*str1 = "ls && ls";
	const char	*str2 = "|| ls";
	const char	*str3 = "(echo ls | grep || hello)";
	const char	*str4 = "echo \"||\"";

	printf("\n=============case 2 - 1====================\n");
	_case(str1, true, "case_two, 52");
	printf("\n=============case 2 - 2====================\n");
	_case(str2, false, "case_two, ");
	printf("\n=============case 2 - 3====================\n");
	_case(str3, true, "case_two, 54");
	printf("\n=============case 2 - 4====================\n");
	_case(str4, true, "case_two, 55");
}

static void	case_three(void)
{
	const char	*str1 = "out < 1 < < 3";
	const char	*str2 = "< 1 hello > 2 > 4 > 5";
	const char	*str3 = "ls < | >";
	const char	*str4 = "ls >               ";
	const char	*str5 = "ls < \"<\"";
	// ls < "<"

	printf("\n=============case 3 - 1====================\n");
	_case(str1, false, "case_three, 69");
	printf("\n=============case 3 - 2====================\n");
	_case(str2, true, "case_three, 70");
	printf("\n=============case 3 - 3====================\n");
	_case(str3, false, "case_three, 71");
	printf("\n=============case 3 - 4====================\n");
	_case(str4, false, "case_three, 72");
	printf("\n=============case 3 - 5====================\n");
	_case(str5, true, "case_three, 73");
}

static void	case_four(void)
{
	const char	*str1 = "ls <<< ls";
	const char	*str2 = "ls <<<< ls";
	const char	*str3 = "ls <<<<< ls";
	const char	*str4 = "ls >> touch";
	const char	*str5 = "ls << \"<<\"";

	printf("\n=============case 4 - 1====================\n");
	_case(str1, false, "case_four 89");
	printf("\n=============case 4 - 2====================\n");
	_case(str2, false, "case_four, 90");
	printf("\n=============case 4 - 3====================\n");
	_case(str3, false, "case_four, 91");
	printf("\n=============case 4 - 4====================\n");
	_case(str4, true, "case_four, 92");
	printf("\n=============case 4 - 4====================\n");
	_case(str5, true, "case_four, 93");
}

void	test_check_syntax_error(void)
{
	case_one();
	case_two();
	case_three();
	case_four();
}
