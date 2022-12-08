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
# include "binary_tree.h"

int g_exit_status;

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
	AND = '&',
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
}	t_token;

typedef struct s_field
{
	t_node			*start_ptr;
	int				len;
}	t_field;

void	tokenize(char *line, t_list *cmd_list);

char	*read_quote_content(char **line, char quote);
char	*read_inside_quote_content(char **line, char quote);
char	*read_group_content(char **line);
char	*read_not_quote_content(char **line);

bool	is_correct_pair(const char *line);
bool	is_even_quote(const char *line);
bool	is_pair_bracket(const char *line);
bool	is_pair_quote(const char *line);

char	*ft_charjoin(char *str, char c);
char	*ft_chardup(char c);

int		get_priority(char *prev_str);
t_token	*create_token(char *prev_str);
void	put_token_in_list(char *prev_str, t_list *list);
bool	parser(t_tree *cmd_tree, t_list *cmd_list);
bool	check_syntax_error(t_tree *cmd_tree);
bool	is_matchable_asterisk(char *dst_file, char *src_file);
void	expand_wildcard(t_token *token);
void	expand_dollar(t_token *token);
t_list	*convert_tree_to_exec_list(t_tree *cmd_tree);
void	remove_quote(t_token *token);
void	expand_field(t_field *field);
void	refine_field(t_field *field, char ***command, char ***redirections);
void	execute(t_list *exec_list, char **envp);

void	b_exit(void);

void	free_token(t_token *token);
void	free_list(t_list *list);
void	free_field(t_tree_node *tree_node);
void	free_tree(t_tree *tree);

#endif