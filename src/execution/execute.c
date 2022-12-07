/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cheseo <cheseo@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:39:03 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/05 15:17:069 by cheseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <fcntl.h>
#include <sys/stat.h>
#include "minishell.h"

bool is_logical_and(char *cmd)
{
	if (ft_strcmp(cmd, "&&") == 0)
		return (true);
	return (false);
}

bool is_logical_or(char *cmd)
{
	if (ft_strcmp(cmd, "||") == 0)
		return (true);
	return (false);
}

void	skip_node_to_logical_operator(t_node **cur_node)
{
	t_field	*cur_field;
	t_token	*start_token;

	while (*cur_node)
	{	
		cur_field = (t_field *)((*cur_node)->content);
		start_token = (t_token *)(cur_field->start_ptr->content);
		if (is_logical_and(start_token->value)
			|| is_logical_or(start_token->value))
			break ;
		(*cur_node) = (*cur_node)->next;
	}
}

// bool	is_builtin(char	*command)
// {
// 	if (ft_strcmp(command, "echo") == 0)
// 	{
// 	}
// 	if (ft_strcmp(command, "cd") == 0)
// 	{
		
// 	}
// 	if (ft_strcmp(command, "pwd") == 0)
// 	{

// 	}
// 	if (ft_strcmp(command, "export") == 0)
// 	{

// 	}
// 	if (ft_strcmp(command, "unset") == 0)
// 	{

// 	}
// 	if (ft_strcmp(command, "env") == 0)
// 	{

// 	}
// 	if (ft_strcmp(command, "exit") == 0)
// 	{

// 	}
// 	return (false);
// }

bool	pipe_connect(t_node *cur_next_node, int fd_pipe[2])
{
	t_token	*token;
	
	if (cur_next_node  == NULL)
		return (false);
	token = (t_token *) ((t_field *)cur_next_node->content)->start_ptr->content;
	if (ft_strcmp(token->value, "|") != 0)
		return (false);
	if (pipe(fd_pipe) == -1)
		ft_terminate("pipe_connect, pipe");
	return (true);
}

void	make_heredoc(char *limiter)
{
	int		fd;
	int		i;
	char	*line;

	fd = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (fd == -1)
		ft_terminate("make_heredoc, open");
	while (1)
	{
		line = readline("> ");
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

bool	redirection(char **redirections, int stdin)
{
	int i;
	int	fd;

	i = 0;
	while (redirections[i])
	{		
		if (ft_strcmp(redirections[i], "<<") == 0)
		{
			dup2(stdin, 0); // heredoc여러개 들어왓을 때 처리하려고 vs pipe랑 heredoc왔을 때 파이프연결을 이게 끊어비림
 			make_heredoc(redirections[i + 1]);
			fd = open("here_doc", O_RDONLY);
			if (fd == -1)
				ft_terminate("redirection, open");
			dup2(fd, 0);
			close(fd);
			unlink("here_doc");
		}
		else if (ft_strcmp(redirections[i], ">>") == 0)
		{
			fd = open(redirections[i + 1], O_CREAT | O_WRONLY | O_APPEND, 0666);
			if (fd == -1)
				ft_terminate("redirection, open");
			dup2(fd, 1);
			close(fd);
		}
		else if (ft_strcmp(redirections[i], "<") == 0)
		{
			fd = open(redirections[i + 1], O_RDONLY);
			if (fd == -1)
				ft_terminate("redirection, open");
			dup2(fd, 0);
			close(fd);
		}
		else if (ft_strcmp(redirections[i], ">") == 0)
		{
			fd = open(redirections[i + 1], O_CREAT | O_TRUNC| O_WRONLY, 0666);
			if (fd == -1)
				ft_terminate("redirection, open");
			dup2(fd, 1);
			close(fd);
		}
		i += 2; 
	}
	close(stdin);
	return (true);
}

void	remove_bracket(char *command)
{
	ft_memmove(command, command + 1, ft_strlen(command));
	command[ft_strlen(command) - 1] = 0;
} 

// char	**put_program_name(char **old_command)
// {
// 	char **new_command;
// 	int	i;

// 	i = 0;
// 	while(old_command[i])
// 		++i;

// 	new_command = ft_calloc(sizeof(char *) * (i + 1), i + 1);
// 	new_command[0] = ft_strdup("minishell");
// 	i = 1;
// 	while(new_command[i])
// 	{
// 		new_command[i] = ft_strdup(old_command[i - 1]);
// 		++i;
// 	}
// 	i = 0;
// 	while (old_command[i])
// 	{
// 		free(old_command[i]);
// 		++i;
// 	}
// 	free(old_command); // 2
// }

// bool	do_subshell(char **command, char **redirections, char **envp,\
// 		int pipe[2], bool has_pipe, int *prev_pipe_in)
// {
// 	pid_t pid;

// 	if (command[0][0] != '(')
// 		return (false);
// 	remove_bracket(*command);
// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (*prev_pipe_in != -1)
// 		{
// 			dup2(*prev_pipe_in, 0);
// 			close(*prev_pipe_in);
// 		}
// 		if (has_pipe)
// 		{
// 			dup2(pipe[1], 1);
// 			close(pipe[1]);
// 			close(pipe[0]);
// 		}
// 		redirection(redirections);
// 		command = put_program_name(command);
// 		execve("./minishell", command, envp);
// 	}
// 	if (*prev_pipe_in != -1)
// 		close(*prev_pipe_in);
// 	if (has_pipe)
// 	{
// 		*prev_pipe_in = pipe[0];
// 		close(pipe[1]);
// 	}
// 	return (true);
// }

// bool	do_builtin(char **command, char **redirections, char **envp,
// 		int pipe[2], bool has_pipe, int *prev_pipe_in)
// {
// 	pid_t	pid;

// 	if (is_builtin(command[0]) == false)
// 		return (false);	
// 	if (has_pipe || *prev_pipe_in != -1)
// 	{
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (*prev_pipe_in != -1)
// 			{
// 				dup2(*prev_pipe_in, 0);
// 				close(*prev_pipe_in);
// 			}
// 			if (has_pipe)
// 			{
// 				dup2(pipe[1], 1);
// 				close(pipe[1]);
// 				close(pipe[0]);
// 			}
// 			redirection(redirections);
// 			exec_builtin(command);
// 		}
// 		if (*prev_pipe_in != -1)
// 			close(*prev_pipe_in);
// 		if (has_pipe)
// 		{
// 			*prev_pipe_in = pipe[0];
// 			close(pipe[1]);
// 		}
// 	}
// 	else
// 	{
// 		redirection(redirections);
// 		exec_builtin(command);
// 	}
// }

char	*find_path(char *command, char **envp)
{
	char	*path;
	char	**path_list;
	int		i;
	struct stat	buf;
	char 	*command_with_path;

	i = 0;
	path = getenv("PATH");
	path_list = ft_split(path, ':');
	while (path_list[i])
	{
		command_with_path = ft_strjoin_left_free(path_list[i], "/");
		command_with_path = ft_strjoin_left_free(command_with_path, command);
		if (lstat(command_with_path, &buf) == 0)
		{
			return (command_with_path);
		}
		++i;
	}
	return (NULL);
}

void execute(t_list *exec_list, char **envp)
{
	t_field	*field;
	t_token	*token;
	
	t_node	*cur_node;
	t_node	*cur_next_node;
	char	**command;
	char	**redirections;
	int		fd_pipe[2];
	int 	prev_pipe_in;
	bool	has_pipe;
	char	*path;
	t_list	*pid_list;
	pid_t	pid;
	int stdin;

	pid_list = init_list();
	prev_pipe_in = -1;
	cur_node = exec_list->head;
	stdin = dup(0);
	while (cur_node)
	{
		cur_next_node = cur_node->next;
		field = (t_field *) cur_node->content;
		token = (t_token *)(field->start_ptr->content);
		if (ft_strcmp(token->value, "|") == 0)                                 
		{
			cur_node = cur_node->next;
			continue ;
		}
		else if (is_logical_and(token->value))
		{	
			waitpid(pid, &g_exit_status, 0);
			// printf("exit status : %d\n", WEXITSTATUS(g_exit_status));
			if (g_exit_status == 0)
			{
				cur_node = cur_node->next;
				continue ;
			}
			else
			{
				cur_node = cur_next_node->next;
				skip_node_to_logical_operator(&cur_node);
				continue ;
			}
		}
		else if (is_logical_or(token->value))
		{
			waitpid(pid, &g_exit_status, 0);
			// printf("exit status : %d\n", WEXITSTATUS(g_exit_status));
			if (g_exit_status == 0)
			{
				cur_node = cur_node->next;
				skip_node_to_logical_operator(&cur_node);
				continue ;
			}
			else
			{
				cur_node = cur_node->next;
				continue ;
			}
		}	
		has_pipe = pipe_connect(cur_next_node, fd_pipe);
		expand_field(field);
		refine_field(field, &command, &redirections); // command_argv 인수추가
		// if (do_subshell(command, redirections, envp, fd_pipe, has_pipe, &prev_pipe_in))
		// {
		// 	cur_node = cur_node->next;
		// 	continue;
		// }
		// if (do_builtin(command, redirections, envp, fd_pipe, has_pipe, &prev_pipe_in))
		// {
		// 	cur_node = cur_node->next;
		// 	continue;
		// }
		pid = fork();
		if (pid == 0)
		{
			if (prev_pipe_in != -1)
			{
				dup2(prev_pipe_in, 0);
				close(prev_pipe_in);
			}
			if (has_pipe)
			{
				dup2(fd_pipe[1], 1);
				close(fd_pipe[1]);
				close(fd_pipe[0]);
			}
			redirection(redirections, stdin);
			if (command[0] == NULL)
				exit(0);
			path = find_path(command[0], envp);
			if (execve(path, command, envp) == -1)
			{
				write(2, "ㄴㅏ능능한한비킴ㅏ\n", 29);
				exit(127);
			}
		}
		push_back(pid_list, make_node((void *)(long long)pid));
		if (prev_pipe_in != -1)
			close(prev_pipe_in);
		if (has_pipe)
		{
			prev_pipe_in = fd_pipe[0];
			close(fd_pipe[1]);
		}
		cur_node = cur_node->next;
	}
	// 여기에서 전부기다리는 것
	while (pid_list->len)
	{
		waitpid((pid_t) pid_list->head->content, &g_exit_status, 0);
		pop_front(pid_list);
	}
	close(stdin);
}

// void	execute(t_list *exec_list)
// {
// 	t_node	*cur_node;
// 	t_field	*cur_field;
// 	t_token	*start_token;

// 	cur_node = exec_list->head;
// 	while (cur_node)
// 	{
// 		cur_field = (t_field *)(cur_node->content);
// 		start_token = (t_token *)(cur_field->start_ptr->content);
// 		if (is_logical_and(start_token->value))
// 		{	
// 			if (g_exit_status == 0)
// 				cur_node = cur_node->next;
// 			else
// 				skip_node_to_logical_operator(&cur_node);
// 		}
// 		else if (is_logical_or(start_token->value))
// 		{
// 			if (g_exit_status == 0)
// 				skip_node_to_logical_operator(&cur_node);
// 			else
// 				cur_node = cur_node->next;
// 		}
// 		else if (ft_strcmp(start_token->value, "|"))
// 		{
// 			cur_node = cur_node->next;
// 		}
// 		else
// 		{
// 			int		fd_pipe[2];
// 			pid_t	pid;
// 			int		cur_pipe_in;
// 			int		cur_pipe_out;
// 			int		prev_pipe_in = -1;
// 			char	**command;

// 			if (cur_node->next == '|')
// 			{
// 				if (pipe(fd_pipe) == -1)
// 					ft_terminate("execute, pipe");
// 				cur_pipe_in = fd_pipe[0];
// 				// fork뜨기 직전에 확장한다?
// 				pid = fork();
// 				if (pid == -1)
// 					ft_terminate("execute, fork");
// 				if (pid == 0)
// 				{
// 					if (prev_pipe_in != -1) // 이전 파이프가 있었으면
// 					{
// 						dup2(prev_pipe_in, 0);
// 						close(prev_pipe_in);
// 					}
// 					dup2(cur_pipe_out, 1);
// 					close(cur_pipe_out);
// 					close(cur_pipe_in);
// 					expand_field(cur_field);
// 					redirectioin();
// 					command = refine_field(cur_field);
// 					execve("/bin/echo", command, envp); // ./minishell, PATH 
// 					// export a=*.c;
// 					// cur_pipe_in을 prev_pipe_in에 담아주면 닫기.
// 				}
// 				// dup 
// 				// expand
// 				// redirection
// 				// argv parsing
// 				// execute
// 			}
// 			else
// 			{
// 				pid = fork();
// 				if (pid == -1)
// 					ft_terminate("execute, fork");
// 				// expand
// 				// redirection
// 				// argv parsing
// 				// execute
// 			{

// 			}
// 			cur_node = cur_node->next;
// 		}
// 		}
// 	// wait_pid
// 	}
// }
	/*
		리스트 순회 - X
		현재 리스트와 다음 리스트를 비교하면서 연산자마다 행동 지정
		현재 노드의 content가 && ,||, |
		오퍼레이터가 아니라면 다음 노드가 파이프 인지 확인
		- 다음 필드가 파이프인지  본다.
			- 파이프를 열여주고 포크하기위해서
		- 지금 필드가 ||, && 라면 
			- exit_status확인해서 
				- &&
					- EXIT_STATUS 가 0이라면 실핸한다.
					- EXIT_STATUS 가 0이아니면 다음 node는 건너뜀 
				- ||
					- EXIT_STATUS 가 0이라면 실행 안하고 다음 node 건너뜀.
					- EXIT_STATUS 가 0이아니면 다음 node 실행 
		- 지금 필드에 리다이렉션(<, >, <<, >>)이 있다면
				- fork()하고 자식에서 이를 처리한다.
		- 지금 필드에 리다이렉션이 있고, 다음 필드에 파이프라면
				- 파이프 셋팅해주고
				- 자식에서 리다이렉션 해주면 된다.                                                                                                                                                                                                                                              
	*/

	/*
		부모
		1. 파이프가 있으면 파이프를 열고
		2. 포크
			자식
			1. 파이프가 열려있으면 파이프셋팅(표준 입출력 셋팅 파이프를 가르키도록)
			2. 확장
			3. 리다이렉션
			4. 정제된 필드 만들기
			5. execv 함수로 넘긴다
		3.  쓰고 있는 파이프 제외하고 다 닫아준다. (+ prev_pipe_in)
		4.부모는 자식이 다음 필드로 간다.
			- 다음 필드가 ||, &&이라면
	*/
