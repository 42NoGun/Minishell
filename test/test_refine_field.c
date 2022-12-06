/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_refine_field.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 16:23:42 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/06 15:55:52 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.h"

static void	do_expand(t_list *exec_list)
{
	t_node	*cur_node;

	cur_node = exec_list->head;
	while (cur_node)
	{
		expand_field(cur_node->content);
		cur_node = cur_node->next;
	}
}

static void	print_exec_list(t_list *exec_list)
{
	t_field	*field;
	char 	**command;
	char 	**redirections;
	int 	i;

	while (exec_list->len)
	{
		field = (t_field *) exec_list->head->content;
		refine_field(field, &command, &redirections);
		i = 0;
		while (command[i])
		{
			if (i == 0)
				printf("[command :]\n");
			printf("{%s}\n", command[i]);
			++i;
		}
		printf("\n");
		i = 0;
		while (redirections[i])
		{
			if (i == 0)
				printf("\n[redirections :]\n");
			printf("{%s}\n", redirections[i]);
			++i;
		}
		printf("\n");
		free(command);
		free(redirections);
		pop_front(exec_list);
	}
	printf("\n");
}

static void	_case(const char *str)
{
	t_list	*cmd_list;
	t_tree	*cmd_tree;
	t_list	*exec_list;

	cmd_list = init_list();
	cmd_tree = init_tree();
	tokenize((char *)str, cmd_list);
	parser(cmd_tree, cmd_list);
	exec_list = convert_tree_to_exec_list(cmd_tree);
	do_expand(exec_list);
	print_exec_list(exec_list);
	free_list(cmd_list); 
	free_tree(cmd_tree);
	free(exec_list);
}
// char	**refine_field(t_field *field)

// (export a='a' && export b='b') > outfile && cat outfile
// export a='a' && export b='b'
// export
// a='a'
// > outfile (pipe setting)
// cat outfile

static void	case_one(void)
{
	const char	*str1 = "a*.c < infile";
	const char	*str2 = "\"ls || ls\" < infile < infile2";
	const char	*str3 = "echo | grep hello << ls && echo hello";
	const char	*str4 = "\"echo\" || export a=*.c";
	const char	*str5 = "ls | ls | ls || ls | ls | ls |";

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

void	test_refined_field(void)
{
	case_one();
}
