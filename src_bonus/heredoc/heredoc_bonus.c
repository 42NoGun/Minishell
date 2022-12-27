/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:18:29 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/27 22:48:15 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell_bonus.h"
#include <readline/readline.h>
#include <fcntl.h>

static void	count_subshell_heredoc(
	char **value, int *heredoc_count, t_list **limiter_list)
{
	while (**value)
	{
		if (**value == '"' || **value == '\'')
			skip_quote_content(value, **value);
		else
		{
			if (**value == '<' && *(*value + 1) == '<')
			{
				++*heredoc_count;
				++(*value);
				push_back_subshell_limiter(*value, *limiter_list);
			}
		}
		++(*value);
	}
}

static int	count_heredoc(t_field *field, int field_len, t_list *limiter_list)
{
	t_node	*cur_node;
	char	*value;
	int		heredoc_count;

	heredoc_count = 0;
	cur_node = field->start_ptr;
	while (field_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(')
			count_subshell_heredoc(&value, &heredoc_count, &limiter_list);
		else
		{
			if (ft_strcmp(value, "<<") == 0)
			{
				++heredoc_count;
				push_back_limiter(cur_node->next, limiter_list);
			}
		}
		cur_node = cur_node->next;
		--field_len;
	}
	return (heredoc_count);
}

static int	check_heredoc(t_list *exec_list, t_list *limiter_list)
{
	t_node		*cur_exec_node;
	t_field		*field;
	int			heredoc_count;

	cur_exec_node = exec_list->head;
	heredoc_count = 0;
	while (cur_exec_node)
	{
		field = (t_field *)cur_exec_node->content;
		heredoc_count += count_heredoc(field, field->len, limiter_list);
		cur_exec_node = cur_exec_node->next;
	}
	return (heredoc_count);
}

static void	write_heredoc(char *file_path, t_list *limiter_list)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = (limiter_list->head->content);
	pop_front(limiter_list);
	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_terminate("open()");
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strcmp(line, limiter) == 0)
		{
			free(line);
			break ;
		}
		_write(fd, line, ft_strlen(line));
		_write(fd, "\n", 1);
		free(line);
	}
	_close(fd);
}

bool	make_heredoc_file(t_list *exec_list)
{
	int			count;
	int			i;
	char		*current_file_sequence;
	char		*current_file_path;
	t_list		*limiter_list;

	i = 0;
	limiter_list = init_list();
	count = check_heredoc(exec_list, limiter_list);
	while (i < count)
	{
		current_file_sequence = ft_itoa(i);
		current_file_path
			= ft_strjoin_right_free("/tmp/heredoc/", current_file_sequence);
		write_heredoc(current_file_path, limiter_list);
		++i;
	}
	free(limiter_list);
	return (true);
}
