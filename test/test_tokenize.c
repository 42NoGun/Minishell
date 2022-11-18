/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tokenize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:10:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/18 11:49:38 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_case(const char *str)
{
	t_list	*list;
	t_token	*content;

	list = init_list();
	tokenize((char *)str, list);
	printf("case : [[%s]]\n", str);
	while (list->len)
	{
		content = (t_token *) list->head->content;
		printf("%s\n", content->value);
		free_token(content);
		pop_front(list);
	}
	free(list);
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

static void	case_one(void)
{	
	const char	*str1 = "echo \"str | \" echo  \" \"| cat -e";
	const char	*str2 = "echo\"str|\"echo\"\"|cat-e";
	const char	*str3 = "echo '$fortytwo \"axs\"' \"ahah\"";
	const char	*str4 = "echo \"$h\'$h\'\"\'$h\'$h";
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

void	test_tokenize(void)
{
	case_one();
	case_two();
	case_three();
	case_four();
}
