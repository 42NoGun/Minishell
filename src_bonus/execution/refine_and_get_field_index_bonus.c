/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_and_get_field_index_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:42:53 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/27 14:55:50 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"

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

void	refine_command(t_token *token)
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

static bool	is_redirection_value(char *value)
{
	if (ft_strncmp(value, "<", 1) == 0 || ft_strncmp(value, ">", 1) == 0)
		return (true);
	return (false);
}

t_token	*get_field_index(t_field *field, int i)
{
	t_node	*cur_node;

	cur_node = field->start_ptr;
	while (i)
	{
		cur_node = cur_node->next;
		--i;
	}
	return ((t_token *)(cur_node->content));
}

bool	*find_to_command_token(t_node *cur_node, int field_len)
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
			to_refine[i] = true;
		cur_node = cur_node->next;
		++i;
	}
	return (to_refine);
}
