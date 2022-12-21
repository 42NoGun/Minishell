/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_and_get_field_index.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanbkim <hanbkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:42:53 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/21 14:21:14 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	remove_quote(char **command, char **refined_command)
{	
	char	*quote_content;

	if (**command == '\'')
	{
		quote_content = read_inside_quote_content(command, '\'');
		*refined_command = ft_strjoin(*refined_command, quote_content);
	}
	else if (**command == '"')
	{
		quote_content = read_inside_quote_content(command, '\"');
		*refined_command = ft_strjoin(*refined_command, quote_content);
	}
	else
	{
		quote_content = read_not_quote_content(command);
		*refined_command = ft_strjoin(*refined_command, quote_content);
	}
}

static void	refine_command(t_token *token)
{
	char	*command;
	char	*refined_command;

	refined_command = ft_strdup("");
	command = token->value;
	while (*command)
	{
		remove_quote(&command, &refined_command);
		++command;
	}
	free(token->value);
	token->value = refined_command;
}

char	*get_field_index_refined_value(t_field *field, int i)
{
	t_node	*cur_node;

	cur_node = field->start_ptr;
	while (i)
	{
		cur_node = cur_node->next;
		--i;
	}
	refine_command(cur_node->content);
	return (((t_token *) cur_node->content)->value);
}

static bool	is_redirection_value(char *value)
{
	if (ft_strncmp(value, "<", 1) == 0 || ft_strncmp(value, ">", 1) == 0)
		return (true);
	return (false);
}

void	find_to_command_token(t_node *cur_node, int field_len,
	bool **refine_ret, int *command_len)
{
	bool	*to_refine;
	t_token	*token;
	int		i;

	i = 0;
	to_refine = ft_calloc(sizeof(bool), field_len);
	while (i < field_len)
	{
		token = (t_token *)(cur_node->content);
		if (is_redirection_value(token->value))
		{
			cur_node = cur_node->next;
			++i;
		}
		else
		{
			to_refine[i] = true;
			++(*command_len);
		}
		cur_node = cur_node->next;
		++i;
	}
	*refine_ret = to_refine;
}
