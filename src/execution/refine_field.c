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

void	expand_field(t_field *field, t_list *env_list, bool is_subshell)
{
	int		len;
	t_token	*cur_token;
	t_node	*cur_node;

	len = field->len;
	cur_node = field->start_ptr;
	if (is_subshell)
		return ;
	while (len)
	{
		cur_token = (t_token *)cur_node->content;
		expand_dollar(cur_token, env_list);
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
	refined = ft_calloc(sizeof(bool), field_len);
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

	cur_node = field->start_ptr;
	while (i)
	{
		cur_node = cur_node->next;
		i--;
	}
	remove_quote(cur_node->content);
	return (((t_token *) cur_node->content)->value);
}
/*
 특수문자 파일은 undefined 지우고  하시기를..
*/
bool is_expanded_wildcard(t_field *field, int i)
{
	t_node	*cur_node;
	char	*value;
	int		index;
	bool	has_quote;
	bool	has_space;

	cur_node = field->start_ptr;
	while (i)
	{
		cur_node = cur_node->next;
		i--;
	}
	value = ((t_token *)(cur_node->content))->value;
	has_quote = false;
	has_space = false;
	index = 0;
	if (value[0] == '(')
		return (false);
	while (value[index])
	{
		if (value[index] == '\"' || value[index] == '\'')
		{
			has_quote = true;
			return (false);
		}
		if (value[index] == ' ')
		{
			has_space = true;
		}
		++index;
	}
	if (has_space)
		return (true);
	return (false);
}

int	ft_count_word_splited(char **wildcard_split)
{
	int	len;

	len = 0;
	while (wildcard_split[len])
	{
		++len;
	}
	return (len);
}

char	**ft_str_realloc(char **ptr, int old_len, int new_len)
{
	char	**new_ptr;
	int		i;

	i = 0;
	new_ptr = calloc(sizeof(char *), new_len);
	while (i < old_len)
	{
		new_ptr[i] = ptr[i];
		++i;
	}
	free(ptr);
	return (new_ptr);
}

void	refine_field(t_field *field, char ***command, char ***redirections)
{
	bool	*refined;
	int		argv_count;
	int		i;
	int		cmd_i;
	int		redir_i;
	char	**wildcard_split;

	argv_count = 0;
	find_refined_token(field->start_ptr, field->len, &refined, &argv_count);
	*command = ft_calloc(sizeof(char *), argv_count + 1); // ls && ls -> 3
	*redirections = ft_calloc(sizeof(char *), field->len - argv_count + 1);
	i = 0;
	cmd_i = 0;
	redir_i = 0;
	int old_command_len = argv_count + 1;
	while (i < field->len)
	{
		if (refined[i] == true)
		{
			// ls hello * -> argv 4개 calloc
			// -> ls hello "hello1 hello2 hello3"
			// * : hello1 hello2 hello3
			// old_command 다 프리해주고
			// new_command (4 -> 6)
			// -> ls hello hello1 hello2 hello3
			// new_command = oldcommand, split 넣어주면 되지 않을까요?
			
			// 1. cat * *
			// 2. echo hello" "hello2
			
			// echo hello * (hello2 hello3)
			if (is_expanded_wildcard(field, i) == true)
			{	
				char *value = get_field_index_refined_value(field, i);
				wildcard_split = ft_split(value, ' ');
				int word_len = ft_count_word_splited(wildcard_split); // 3
				int new_command_len = old_command_len + word_len - 1;
				*command = ft_str_realloc(*command, old_command_len, new_command_len);
				old_command_len = new_command_len;
				int j = 0;
				while (wildcard_split[j])
				{
					(*command)[cmd_i++] = wildcard_split[j];
					++j;
				}
				free(wildcard_split);
			}
			else
			{
				(*command)[cmd_i++] = ft_strdup(get_field_index_refined_value(field, i));
			}
		}
		else
		{
			(*redirections)[redir_i++] = ft_strdup(get_field_index_refined_value(field, i));
		}
		++i;
	}
	// printf("refine_field, command[0]: %p\n", (*command)[0]);
	free(refined);
}
