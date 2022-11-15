#include "minishell.h"
#include "test.h"

// static void	case_two(void)
// {
// 	const char	*str1 = "$ <<ls > pwd ||| ls>>>>> <<<";
// 	const char	*str2 = "$ > pwd || ls && ls";
// 	const char	*str3 = "echo $HOME \"$\"HOME \"$HOME\" $''HOME $\"\"HOME $HO\"\"ME $\"HOME\"";
// 	const char	*str4 = "exporta='a'&&echo$?";
// 	const char	*str5 = "(echo \"str | \") echo  \" \"| cat -e";

// 	printf("\n=============case 2 - 1====================\n");
// 	_case(str1);
// 	printf("\n=============case 2 - 2====================\n");
// 	_case(str2);
// 	printf("\n=============case 2 - 3====================\n");
// 	_case(str3);
// 	printf("\n=============case 2 - 4====================\n");
// 	_case(str4);
// 	printf("\n=============case 2 - 5====================\n");
// 	_case(str5);
// }

// static void	case_three(void)
// {
// 	const char	*str1 = "echo '$fortytwo \"axs\"' \"aha- $fortytwo \"axs ah-";
// 	const char	*str2 = "grep \"hello\" && grep \"h\" <<mks";
// 	const char	*str3 = "(ls | ls && (ls && ls | ls)) || ls  >> filepath";
// 	const char	*str4 = "echo \"str | \" echo  \" \"| cat -e";
// 	const char	*str5 = "     echo( \"str||\"echo)  \" \"|cat -e";

// 	printf("\n=============case 3 - 1====================\n");
// 	_case(str1);
// 	printf("\n=============case 3 - 2====================\n");
// 	_case(str2);
// 	printf("\n=============case 3 - 3====================\n");
// 	_case(str3);
// 	printf("\n=============case 3 - 4====================\n");
// 	_case(str4);
// 	printf("\n=============case 3 - 5====================\n");
// 	_case(str5);
// }

// static void	case_four(void)
// {
// 	const char	*str1 = "echo(HOME)";
// 	const char	*str2 = "ls|(HOME)\"(cat)\"|(ls) | (ls)";
// 	const char	*str3 = "echo $(grep hello))";
// 	const char	*str4 = "echo 2|>1";

// 	printf("\n=============case 4 - 1====================\n");
// 	_case(str1);
// 	printf("\n=============case 4 - 2====================\n");
// 	_case(str2);
// 	printf("\n=============case 4 - 3====================\n");
// 	_case(str3);
// 	printf("\n=============case 4 - 4====================\n");
// 	_case(str4);
// }
static void	_case(const char *str, bool flag, char *error_message)
{
    t_list	*cmd_list;
	t_tree	*cmd_tree;

	cmd_list = init_list();
	cmd_tree = init_tree();
    tokenize((char *)str, cmd_list);
    parser(cmd_tree, cmd_list);
	ft_assert(check_syntax_error(cmd_tree), flag, error_message);
}

static void	case_one(void)
{
	const char	*str1 = "ls |";
	const char	*str2 = "ls ||||||| ls";
	const char	*str3 = "echo | grep hello | ls &&";
	const char	*str4 = "||";
	const char	*str5 = "ls | ls | ls || ls | ls | ls |";

	printf("\n=============case 1 - 1====================\n");
	_case(str1, false, "case_one 75");
	printf("\n=============case 1 - 2====================\n");
	_case(str2, false, "case_one, 76");
	printf("\n=============case 1 - 3====================\n");
	_case(str3, false, "case_one, 77");
	printf("\n=============case 1 - 4====================\n");
	_case(str4, false, "case_one 78");
	printf("\n=============case 1 - 5====================\n");
	_case(str5, false, "case_one, 79");
}

static void	case_two(void)
{
	const char	*str1 = "ls && ls";
	const char	*str2 = "|| ls";
	const char	*str3 = "(echo ls | grep || hello)";
	const char	*str4 = "echo \"||\"";

	printf("\n=============case 4 - 1====================\n");
	_case(str1, true, "case_one 100");
	printf("\n=============case 4 - 2====================\n");
	_case(str2, false, "case_two, 102");
	printf("\n=============case 4 - 3====================\n");
	_case(str3, true, "case_tree, 104");
	printf("\n=============case 4 - 4====================\n");
	_case(str4, true, "case_four 106");
}

void    test_check_syntax_error(void)
{
    case_one();
    case_two();
}

