/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refine_field.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanbkim <hanbkim@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/20 11:42:53 by hanbkim           #+#    #+#             */
/*   Updated: 2022/12/20 15:40:10 by hanbkim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

bool	is_expanded_wildcard(char *value)
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

void	convert_wildcard_to_command_list(char ***command, int *cmd_i, int argv_count, char *value)
{
	char	**wildcard_split;
	int		old_command_len;
	int		word_len;
	int		new_command_len;
	int		j;

	old_command_len = argv_count + 1;
	wildcard_split = ft_split(value, ' ');
	word_len = ft_count_word_splited(wildcard_split);
	new_command_len = old_command_len + word_len - 1;
	*command = ft_str_realloc(*command, old_command_len, new_command_len);
	old_command_len = new_command_len;
	j = 0;
	while (wildcard_split[j])
		(*command)[(*cmd_i)++] = wildcard_split[j++];
	free(wildcard_split);
}

void	refine_field(t_field *field, char ***command, char ***redirections, int i)
{
	bool	*refine;
	int		argv_count;
	int		cmd_i;
	int		redir_i;
	char	*value;

	argv_count = 0;
	find_to_refine_token(field->start_ptr, field->len, &refine, &argv_count);
	*command = ft_calloc(sizeof(char *), argv_count + 1);
	*redirections = ft_calloc(sizeof(char *), field->len - argv_count + 1);
	i = 0;
	cmd_i = 0;
	redir_i = 0;
	while (i < field->len)
	{
		value = get_field_index_refined_value(field, i);
		if (refine[i] == true)
		{
			if (is_expanded_wildcard(value) == true)
				convert_wildcard_to_command_list(command, &cmd_i, argv_count, value);
			else
				(*command)[cmd_i++] = ft_strdup(value);
		}
		else
			(*redirections)[redir_i++] = ft_strdup(value);
		++i;
	}
	free(refine);
}
