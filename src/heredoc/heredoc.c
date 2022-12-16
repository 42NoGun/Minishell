/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 17:18:29 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/16 17:22:41 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>
#include <fcntl.h>

void	skip_quote_content(char **value, char quote)
{
	size_t	len;

	len = ft_strchr((*value + 1), quote) - *value;
	*value += len;
}

void	push_back_limiter(t_node *node, t_list *limiter_list)
{
	char	*value;

	value = ((t_token *)node->content)->value;
	push_back(limiter_list, make_node(ft_strdup(value)));
}

char	*get_limiter(char *value)
{
	int	end;

	end = 0;
	while (value[end])
	{
		if (!ft_isalnum(value[end]))
			break ;
		++end;
	}
	return (ft_substr(value, 0, end));
}

void	push_back_subshell_limiter(char *value, t_list *limiter_list)
{
	char	*limiter;

	++value;
	while (*value && *value == ' ')
		++value;
	limiter = get_limiter(value);
	push_back(limiter_list, make_node(limiter));
}

int	count_heredoc(t_field *field, int field_len, t_list *limiter_list)
{
	t_node	*cur_node;
	char	*value;
	int		loop_len;
	int		heredoc_count;

	heredoc_count = 0;
	cur_node = field->start_ptr;
	while (field_len)
	{
		value = ((t_token *)cur_node->content)->value;
		if (value[0] == '(')
		{		
			while (*value)
			{
				if (*value == '"' || *value == '\'')
					skip_quote_content(&value, *value);
				else
				{
					if (*value == '<' && *(value + 1) == '<')
					{
						++heredoc_count;
						++value; // 커서가 두번째 <에 있어요
						push_back_subshell_limiter(value, limiter_list);
					}
				}
				++value;
			}
		}
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

int check_heredoc(t_list *exec_list, t_list *limiter_list)
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

void	write_heredoc(char *file_path, t_list *limiter_list)
{
	int		fd;
	int		i;
	char	*line;
	char	*limiter;


	limiter = (limiter_list->head->content);
	pop_front(limiter_list);
	fd = open(file_path, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_terminate("write_heredoc, open");
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
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

bool	make_heredoc_file(t_list *exec_list)
{
	int			count;
	int			i;
	int			fd;
	char		*current_file_sequence;
	char		*current_file_path;
	const char	*file_name_prefix = "/tmp/heredoc/";
	t_list		*limiter_list;

	i = 0;
	limiter_list = init_list();
	count = check_heredoc(exec_list, limiter_list);
	while (i < count)
	{
		current_file_sequence = ft_itoa(i);
		current_file_path = ft_strjoin_right_free(file_name_prefix, current_file_sequence);
		write_heredoc(current_file_path, limiter_list);
		++i;
	}
	free(limiter_list);
	return (true);
}
