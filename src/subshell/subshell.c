/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:15:57 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/19 12:21:25 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strlen_no_space(char *str)
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

bool	has_subshell_error(t_field *field, int redirection_len)
{
	t_node	*cur_node;
	int		value_len;
	int		i;
	char	*value;
	int		loop_len;

	loop_len = field->len;
	cur_node = field->start_ptr;
	while (loop_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(' && ft_strlen_no_space(value) == 2) // (공백 있는 경우)
			return (true);
		if (value[0] == '(' && ((field->len - redirection_len) != 1)) // () 토큰이 붙었을 때
			return (true);
		cur_node = cur_node->next;
		--loop_len;
	}
	return (false);
}

static bool	is_redirection_value(char *value)
{
	if (ft_strncmp(value, "<", 1) == 0 || ft_strncmp(value, ">", 1) == 0)
		return (true);
	return (false);
}

int	count_field_len(t_field *field)
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
		if (is_redirection_value(value))
			++field_len;
		--len;
		cur_node = cur_node->next;
	}
	return (2 * field_len);
}

bool	check_bracket_syntax_error(t_list *exec_list)
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

void	subshell_logic(int argc, char **argv, t_list *env_list)
{
	int	i;

	t_list *cmd_list;
	t_tree *cmd_tree;
	t_list *cmd_exec_list;
	char *line;

	cmd_list = init_list();
	cmd_tree = init_tree();
	line = ft_strdup(argv[1]);
	if (ft_strcmp(line, "") == 0)
	{
		free(line);
		return ;
	}
	if (is_correct_pair(line) == false)
	{
		free(line);
		return ;
	}
	tokenize(line, cmd_list);
	parser(cmd_tree, cmd_list);
	if (check_syntax_error(cmd_tree) == false)
	{
		free(line);
		return ;
	}
	cmd_exec_list = convert_tree_to_exec_list(cmd_tree);
	if (check_bracket_syntax_error(cmd_exec_list) == false)
	{
		free(line);
		return ;
	}
	execute(cmd_exec_list, env_list);
	free(line);
}
