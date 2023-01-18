/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:57 by jiyunpar          #+#    #+#             */
/*   Updated: 2023/01/18 14:22:20 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

static int	ft_strlen_no_space(char *str)
{
	int	i;
	int	len;

	i = 0;
	len = 0;
	while (str[i])
	{
		if (str[i] != ' ')
			++len;
		++i;
	}
	return (len);
}

static bool	has_subshell_error(t_field *field, int redirection_len)
{
	t_node	*cur_node;
	char	*value;
	int		loop_len;

	loop_len = field->len;
	cur_node = field->start_ptr;
	while (loop_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(' && ft_strlen_no_space(value) == 2)
			return (true);
		if (value[0] == '(' && ((field->len - redirection_len) != 1))
			return (true);
		cur_node = cur_node->next;
		--loop_len;
	}
	return (false);
}

static int	count_field_len(t_field *field)
{
	t_node	*cur_node;
	int		len;
	char	*value;
	int		field_len;

	field_len = 0;
	cur_node = field->start_ptr;
	len = field->len;
	while (len)
	{
		value = ((t_token *)(cur_node->content))->value;
		if (ft_strncmp(value, "<", 1) == 0 || ft_strncmp(value, ">", 1) == 0)
			++field_len;
		--len;
		cur_node = cur_node->next;
	}
	return (2 * field_len);
}

bool	is_valid_bracket_subshell(t_list *exec_list)
{
	t_node		*cur_exec_node;
	t_field		*field;
	int			redirection_len;

	cur_exec_node = exec_list->head;
	while (cur_exec_node)
	{
		field = (t_field *)cur_exec_node->content;
		redirection_len = count_field_len(field);
		if (has_subshell_error(field, redirection_len))
		{
			ft_putstr_fd("minishell : subshell syntax error\n", 2);
			g_exit_status = 2 << 8;
			return (false);
		}
		cur_exec_node = cur_exec_node->next;
	}
	return (true);
}

int	do_subshell(int argc, char **argv, t_list *env_list)
{
	t_tree	*cmd_tree;
	t_list	*cmd_list;
	char	*line;

	(void)argc;
	if (ft_strlen(argv[1]) == 0)
		line = ft_strdup("\"\"");
	else
		line = ft_strdup(argv[1]);
	if (is_correct_pair(line) == false)
		return (WEXITSTATUS(g_exit_status));
	cmd_tree = make_tree(tokenize(line));
	if (!is_valid_operator_or_redirection(cmd_tree))
		return (WEXITSTATUS(g_exit_status));
	cmd_list = convert_tree_to_exec_list(cmd_tree);
	if (!is_valid_bracket_subshell(cmd_list))
		return (WEXITSTATUS(g_exit_status));
	execute(cmd_list, env_list);
	return (WEXITSTATUS(g_exit_status));
}
