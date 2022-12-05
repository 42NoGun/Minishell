/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_convert_tree_to_list.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 11:15:37 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/01 14:04:599 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"
#include "minishell.h"

static void	print_field(t_field *field)
{
	while (field->len > 0)
	{
		printf("{%s}", ((t_token *)(field->start_ptr->content))->value);
		--field->len;
		field->start_ptr = field->start_ptr->next;
	}
	printf("\n");
}

static void	print_exec_list(t_list *exec_list)
{
	t_field	*content;

	while (exec_list->len)
	{
		content = (t_field *) exec_list->head->content;
		print_field(content);
		pop_front(exec_list);
	}
}

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

static void	case_one(void)
{
	const char	*str1 = "$a";
	const char	*str2 = "\"hello\"$USER\"hello\"";
	const char	*str3 = "\"*.c hello $PATHhello $PATH hello\"";
	const char	*str4 = "echo hello < 1 && echo lehohe < 2";
	const char	*str5 = "(cat hello) < infile | grep hello < infile";

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

void	test_convert_tree_to_exec_list(void)
{
	case_one();
}
