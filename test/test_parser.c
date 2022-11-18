/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 13:33:16 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/18 11:49:49 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_field(t_tree_node *tree_node)
{
	t_field	*field;

	field = (t_field *) tree_node->content;
	while (field->len > 0)
	{
		printf("{%s}", ((t_token *)(field->start_ptr->content))->value);
		--field->len;
		field->start_ptr = field->start_ptr->next;
	}
	printf("\n");
}

static void	_case(const char *str)
{
	t_list	*cmd_list;
	t_tree	*cmd_tree;

	cmd_list = init_list();
	cmd_tree = init_tree();
	tokenize((char *)str, cmd_list);
	parser(cmd_tree, cmd_list);
	inorder_traverse(cmd_tree->root, print_field);
	free_list(cmd_list);
	free_tree(cmd_tree);
}

static void	case_one(void)
{
	const char	*str1 = "echo | hello < infile | (grep hello)";
	const char	*str2 = "grep \"h\" << limit";
	const char	*str3 = "echo | grep hello | ls |";
	const char	*str4 = "<infile | echo \"hello\" | grep h";
	const char	*str5 = "export a='a' && echo $?";

	printf("\n=============case 1 - 1====================\n");
	_case(str1);
	printf("\n=============case 1 - 2====================\n");
	_case(str2);
	printf("\n=============case 1 - 3====================\n");
	_case(str3);
	printf("\n=============case 1 - 4====================\n");
	_case(str4);
	printf("\n=============case 1 - 5====================\n");
	_case(str5);
}

static void	case_two(void)
{
	const char	*str1 = "$ <<ls > pwd ||| ls>>>>> <<<";
	const char	*str2 = "$ > pwd || ls && ls";
	const char	*str3 = "echo $HOME \"$\"HOME \"$HOME\" $''HOME $\"\"HOME $HO\"\"ME $\"HOME\"";
	const char	*str4 = "exporta='a'&&echo$?";
	const char	*str5 = "(echo \"str | \") echo  \" \"| cat -e";

	printf("\n=============case 2 - 1====================\n");
	_case(str1);
	printf("\n=============case 2 - 2====================\n");
	_case(str2);
	printf("\n=============case 2 - 3====================\n");
	_case(str3);
	printf("\n=============case 2 - 4====================\n");
	_case(str4);
	printf("\n=============case 2 - 5====================\n");
	_case(str5);
}

static void	case_three(void)
{
	const char	*str1 = "echo '$fortytwo \"axs\"' \"aha- $fortytwo \"axs ah-";
	const char	*str2 = "grep \"hello\" && grep \"h\" <<mks";
	const char	*str3 = "(ls | ls && (ls && ls | ls)) || ls  >> filepath";
	const char	*str4 = "echo \"str | \" echo  \" \"| cat -e";
	const char	*str5 = "     echo( \"str||\"echo)  \" \"|cat -e";

	printf("\n=============case 3 - 1====================\n");
	_case(str1);
	printf("\n=============case 3 - 2====================\n");
	_case(str2);
	printf("\n=============case 3 - 3====================\n");
	_case(str3);
	printf("\n=============case 3 - 4====================\n");
	_case(str4);
	printf("\n=============case 3 - 5====================\n");
	_case(str5);
}

static void	case_four(void)
{
	const char	*str1 = "echo(HOME)";
	const char	*str2 = "ls|(HOME)\"(cat)\"|(ls) | (ls)";
	const char	*str3 = "echo $(grep hello))";
	const char	*str4 = "echo 2|>1";

	printf("\n=============case 4 - 1====================\n");
	_case(str1);
	printf("\n=============case 4 - 2====================\n");
	_case(str2);
	printf("\n=============case 4 - 3====================\n");
	_case(str3);
	printf("\n=============case 4 - 4====================\n");
	_case(str4);
}

void	test_parser(void)
{
	printf("\n\n\n\n============test_parser============\n\n\n\n");
	case_one();
	case_two();
	case_three();
	case_four();
}
