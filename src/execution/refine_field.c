/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 13:39:09 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/05 15:28:07by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_field(t_field *field)
{
	int		len;
	t_token	*cur_token;
	t_node	*cur_node;

	len = field->len;
	cur_node = field->start_ptr;
	while (len)
	{
		cur_token = (t_token *)cur_node->content;
		expand_dollar(cur_token);
		expand_wildcard(cur_token);
		cur_node = cur_node->next;
		--len;
	}
}

bool	is_redirection_value(char *value)
{
	if (ft_strncmp(value, "<", 1) == 0 || ft_strncmp(value, ">", 1) == 0)
		return (true);
	return (false);
}

void	find_refined_token(t_node *cur_node, int field_len,
	bool **refined_ret, int *command_len)
{
	bool	*refined;
	t_token	*token;
	int		i;

	i = 0;
	refined = ft_calloc(sizeof(bool) * field_len, field_len);
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
			refined[i] = true;
			++(*command_len);
		}
		cur_node = cur_node->next;
		++i;
	}
	*refined_ret = refined;
}

void	remove_quote(t_token *token)
{
	char	*command;
	char	*quote_content;
	char	*refined_command;

	refined_command = ft_strdup("");
	command = token->value;
	while (*command)
	{
		if (*command == '\'')
		{
			quote_content = read_inside_quote_content(&command, '\'');
			refined_command = ft_strjoin(refined_command, quote_content);
		}
		else if (*command == '"')
		{
			quote_content = read_inside_quote_content(&command, '\"');
			refined_command = ft_strjoin(refined_command, quote_content);
		}
		else
		{
			quote_content = read_not_quote_content(&command);
			refined_command = ft_strjoin(refined_command, quote_content);
		}
		++command;
	}
	free(token->value);
	token->value = refined_command;
}

char	*get_field_index_refined_value(t_field *field, int i)
{
	t_node	*cur_node;
	char	*value;

	cur_node = field->start_ptr;
	while (i)
	{
		cur_node = cur_node->next;
		i--;
	}
	value = ((t_token *)(cur_node->content))->value;
	remove_quote(cur_node->content);
	return (((t_token *) cur_node->content)->value);
}

void	refine_field(t_field *field, char ***command, char ***redirections)
{
	bool	*refined;
	int		argv_count;
	int		i;
	int		cmd_i;
	int		redir_i;

	argv_count = 0;
	find_refined_token(field->start_ptr, field->len, &refined, &argv_count);
	*command = ft_calloc(sizeof(char *) * (argv_count + 1), argv_count + 1);
	*redirections = ft_calloc(sizeof(char *) * (field->len - argv_count + 1), field->len - argv_count + 1);
	i = 0;
	cmd_i = 0;
	redir_i = 0;
	while (i < field->len)
	{
		if (refined[i] == true)
		{
			(*command)[cmd_i++] = get_field_index_refined_value(field, i);
		}
		else
		{
			(*redirections)[redir_i++] = get_field_index_refined_value(field, i);
		}
		++i;
	}
	free(refined);
}
