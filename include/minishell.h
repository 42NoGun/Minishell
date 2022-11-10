/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:03:43 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/01 11:09:56by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <termios.h>
# include "libft.h"
# include "linked_list.h"

enum	e_operator
{
	PIPE = '|',
	IN_REDIR = '<',
	OUT_REDIR = '>',
	OUT_REDIR_APPEND = '>' + '>',
	HEREDOC = '<' + '<',
	SINGLE_QUOTE = '\'',
	DOUBLE_QUOTE = '\"',
	OR = '|' + '|',
	AND = '&' + '&',
	DOLLAR = '$',
	WILDCARD = '*',
	OPEN_BRACKET = '(',
	CLOSE_BRACKET = ')',
	Q_MARK = '?',
	CMD = 'c',
};

typedef struct s_token
{
	char			*value;
	int				priority;
	enum e_operator	type;
}	t_token;


void	tokenize(const char *line, t_list *cmd_list);
char	*read_quote_content(char **line, char quote);
bool	is_correct_pair(const char *line);
bool	is_even_quote(const char *line);
bool	is_pair_bracket(const char *line);
char	*ft_charjoin(char *str, char c);
char	*ft_chardup(char c);
int		get_priority(char *prev_str);
t_token	*create_token(char *prev_str);
void	put_token_in_list(char *prev_str, t_list *list);

#endif