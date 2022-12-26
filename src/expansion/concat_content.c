/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   concat_content.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/26 13:45:47 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	expand_exit_status(char **expanded_content)
{
	char	*converted_env_content;

	converted_env_content = ft_itoa(WEXITSTATUS(g_exit_status));
	*expanded_content = ft_strjoin(*expanded_content, converted_env_content);
}

static void	expand_environment_value(char **expanded_content, char *env_content,
	t_list *env_list)
{
	char	*converted_env_content;

	converted_env_content = ft_getenv(env_list, env_content);
	if (converted_env_content)
		*expanded_content = ft_strjoin_left_free(*expanded_content,
				converted_env_content);
}

static bool	is_expand_delimiter(char c)
{
	if (ft_isalnum(c) || c == '?' || c == '_')
		return (true);
	return (false);
}

void	concatenate_expanded_content(char **expanded_content, char **content,
	char **command, t_list *env_list)
{
	int		env_content_len;
	char	*env_content;

	env_content_len = 0;
	while (**content && is_expand_delimiter(**content))
	{
		++(*content);
		++env_content_len;
		if (*(*content - 1) == '?')
			break ;
	}
	env_content = ft_substr(*content - env_content_len, 0, env_content_len);
	if (ft_strlen(env_content) < 1 && ft_strlen(*command) == 1)
		*expanded_content = ft_strjoin_left_free(*expanded_content, "$");
	else if (ft_strncmp(env_content, "?", 1) == 0)
		expand_exit_status(expanded_content);
	else
		expand_environment_value(expanded_content, env_content, env_list);
	free(env_content);
}

void	concatenate_not_expanded_content(char **expanded_content,
	char **content)
{
	int		meet_before_dollar_len;
	char	*not_expanded_content;

	meet_before_dollar_len = 0;
	while (**content && **content != '$')
	{
		++meet_before_dollar_len;
		++(*content);
	}
	not_expanded_content = ft_substr(*content - meet_before_dollar_len, 0,
			meet_before_dollar_len);
	*expanded_content = ft_strjoin(*expanded_content, not_expanded_content);
}
