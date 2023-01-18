/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_bonus.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 11:03:43 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/25 21:40:55 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_BONUS_H
# define MINISHELL_BONUS_H
# include <unistd.h>
# include <stdlib.h>
# include <errno.h>
# include <stdbool.h>
# include <stdio.h>
# include <termios.h>
# include "libft.h"
# include "linked_list_bonus.h"
# include "binary_tree_bonus.h"

int	g_exit_status;

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

typedef struct s_pipe
{
	bool	has_pipe;
	int		fd_pipe[2];
	int		prev_pipe_in;
	int		std_in;
	int		std_out;
}	t_pipe;

typedef struct s_pid
{
	t_list	*pid_list;
	pid_t	pid;
}	t_pid_utils;

typedef struct s_context
{
	char	**command;
	char	**redirections;
}	t_context;

static __inline t_field	*get_field(t_node *node)
{
	return (node->content);
}

static __inline char	*get_value(t_node *node)
{
	return (((t_token *)(get_field(node)->start_ptr->content))->value);
}

static __inline char	is_subshell(t_node *node)
{
	return (get_value(node)[0] == '(');
}

/*src_bonus/built_in/*/
int		b_pwd(void);
int		b_cd(char **command, t_list *env_list);
int		b_echo(char **commands);
int		b_env(char **command, t_list *env_list);
int		b_exit(char **command, bool parent);
int		b_export(char **command, t_list *env_list);
int		b_unset(char **command, t_list *env_list);
void	print_export(t_list *env_list);
void	do_builtin(char **command, t_list *env_list, bool parent);
bool	do_parent_builtin(t_node **cur_node,
							t_list *env_list, t_context *c, t_pipe *p);

/*src/built_in/export_utils.c*/
bool	is_valid_key(char *key);

/*src_bonus/execution*/
pid_t	do_child_process(t_context *c, t_list *env_list,
							bool is_subshell, t_pipe *p);
t_list	*convert_tree_to_exec_list(t_tree *cmd_tree);
void	execute(t_list *exec_list, t_list *env_list);
bool	pipe_connect(t_node *cur_next_node, t_pipe *p);
bool	do_pipe(t_node **cur_node, char *token);
void	set_child_pipe(t_pipe *p, t_context *c);
void	init_execute_utils(t_pipe *pipe_utils, t_pid_utils *process);
bool	heredoc(char **redirections, int std_in, bool parent);
bool	redirection(char **redirections, bool parent);
bool	*find_to_command_token(t_node *cur_node, int field_len);
t_token	*get_field_index(t_field *field, int i);
void	refine_field(t_field *field, char ***command, char ***redirections);
void	refine_command(t_token *token);
void	find_path(char **command, t_list *env_list);

/*src_bonus/expansion*/
void	concatenate_not_expanded_content(char **expanded_content,
							char **content);
void	concatenate_expanded_content(char **expanded_content, char **content,
							char **command, t_list *env_list);
char	*read_not_quote_content(char **line);
void	expand_dollar(t_token *token, t_list *env_list);
void	expand_wildcard(t_token *token);
void	expand_field(t_field *field, t_list *env_list, bool is_subshell);

/*src_bonus/heredoc*/
void	skip_quote_content(char **value, char quote);
void	push_back_limiter(t_node *node, t_list *limiter_list);
void	push_back_subshell_limiter(char *value, t_list *limiter_list);
char	*get_heredoc_file_path(void);
bool	make_heredoc_file(t_list *exec_list);

/*src_bonus/parser*/
bool	is_correct_pair(const char *line);
bool	is_valid_operator_or_redirection(t_tree *cmd_tree);
t_tree	*make_tree(t_list *cmd_list);
bool	can_parse(t_list **tokenized_list, t_tree **cmd_tree,
							t_list **cmd_list, char *line);
void	put_token_double_operator(char **prev_str, char **line,
							t_list *cmd_list);
void	put_token_single_operator_no_space(char **prev_str, char **line,
							t_list *cmd_list);
void	put_token_single_operator(char **prev_str, char **line,
							t_list *cmd_list);
void	put_token_bracket_content(char **prev_str, char **line,
							t_list *cmd_list);
void	put_token_before_space(char **prev_str, char **line,
							t_list *cmd_list);
char	*read_quote_content(char **line, char quote);
char	*read_inside_quote_content(char **line, char quote);
char	*read_group_content(char **line);
bool	is_bracket(char c);
bool	is_quote(char c);
bool	is_operator(char c);
bool	is_space(char c);
char	*ft_charjoin(char *str, char c);
char	*ft_chardup(char c);
void	put_token_in_list(char *prev_str, t_list *list);
t_list	*tokenize(char *line);

/*src_bonus/signal*/
void	define_signal(void);

/*src_bonus/subshell*/
bool	is_valid_bracket_subshell(t_list *exec_list);
int		do_subshell(int argc, char **argv, t_list *env_list);

/*src_bonus/utils*/
void	remove_bracket(char *command);
bool	is_builtin(char	*command);
bool	is_logical_or(char *cmd);
bool	is_logical_and(char *cmd);
bool	is_pipe(char *cmd);
void	free_token(t_token *token);
void	free_list_node_token(t_list *list);
void	free_field(t_tree_node *tree_node);
void	free_tree_node_field(t_tree *tree);
void	free_list_only_node(t_list *list);
void	free_list_node_content(t_list *list);
void	free_2d_str(char **arr_str);
void	free_rest(t_list *tokenized_list,
							t_tree *cmd_tree, t_list *cmd_list);
char	*ft_getenv(t_list *env_list, char *env);
void	ft_setenv(t_list *env_list, char *key, char *command);
char	*get_key(char *command, char *value);
char	*get_value_env(char *command);
char	*get_value_export(char *command);
void	copy_envp(t_list *env_list, char **envp);
char	**list_to_2d_array(t_list *envp_list);
char	*get_line(void);
t_list	*init_environment(char **envp);
int		add_history_line(char *line);
bool	is_line_null(char *line);
bool	has_line_content(char *line);
void	make_heredoc(t_list *cmd_list);
bool	is_catched_interrupt(t_list *tokenized_list,
							t_tree *cmd_tree, t_list *cmd_list);

#endif
