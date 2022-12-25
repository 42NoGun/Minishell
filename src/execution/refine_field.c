/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:42:53 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/25 20:29:02 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_expanded_wildcard(char *value)
{
	int		index;

	if (value[0] == '(')
		return (false);
	index = 0;
	while (value[index])
	{
		if (value[index] == '\"' || value[index] == '\'')
			return (false);
		if (value[index] == ' ')
			return (true);
		++index;
	}
	return (false);
}

static char	**list_to_array(t_list *list)
{
	char	**ret;
	int		i;

	ret = ft_calloc(sizeof(char *), list->len + 1);
	i = 0;
	while (list->len)
	{
		ret[i++] = ft_strdup(list->head->content);
		free(list->head->content);
		pop_front(list);
	}
	free(list);
	return (ret);
}

static void	push_command(t_list *cmd_list, char *value)
{
	char	**wildcard_split;
	int		i;

	if (is_expanded_wildcard(value) == false)
	{
		push_back(cmd_list, make_node(ft_strdup(value)));
		return ;
	}
	wildcard_split = ft_split(value, ' ');
	i = 0;
	while (wildcard_split[i])
	{
		push_back(cmd_list, make_node(wildcard_split[i]));
		++i;
	}
	free(wildcard_split);
}

void	refine_field(t_field *field, char ***command, char ***redirections)
{
	bool	*is_command;
	char	*value;
	t_list	*cmd_list;
	t_list	*redir_list;
	int		i;

	is_command = find_to_command_token(field->start_ptr, field->len);
	cmd_list = init_list();
	redir_list = init_list();
	i = 0;
	while (i < field->len)
	{
		value = get_field_index_refined_value(field, i);
		if (is_command[i] == true)
			push_command(cmd_list, value);
		else
			push_back(redir_list, make_node(ft_strdup(value)));
		++i;
	}
	*command = list_to_array(cmd_list);
	*redirections = list_to_array(redir_list);
	free(is_command);
}
