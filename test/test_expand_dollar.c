/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_dollar.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:00:06 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/07 14:15:07 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token	*make_token(char *value, int priority)
{
	t_token	*token;

	token = malloc(sizeof(t_token));
	token->value = ft_strdup(value);
	token->priority = priority;
	return (token);
}

void	test_expand_dollar(void)
{
	t_token	*token1;
	t_token	*token2;
	t_token	*token3;
	t_token	*token4;
	t_token	*token5;

	printf("\n=======\"$PATH\"=================\n");
	token1 = make_token("\"$?'$PATH'\"", 2);
	expand_dollar(token1);
	printf("%s\n", token1->value);
	printf("\n==============================================\n");
	token2 = make_token("\"hello\"$USER\"hello\"", 2);
	expand_dollar(token2);
	printf("%s\n", token2->value);
	printf("\n==============================================\n");
	token3 = make_token("\"hello hello $PATHhello $PATH hello\"", 2);
	expand_dollar(token3);
	printf("%s\n", token3->value);
	printf("\n==============================================\n");
	token4 = make_token("\"hello hello \"$PATH\"hello hello\"", 2);
	expand_dollar(token4);
	printf("%s\n", token4->value);
	printf("\n==============================================\n");
	token5 = make_token("$PATH$USER'$USER'''$USER''", 2);
	expand_dollar(token5);
	printf("%s\n", token5->value);
	free_token(token1);
	free_token(token2);
	free_token(token3);
	free_token(token4);
	free_token(token5);
}