/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_expand_wildcard.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:56:10 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/18 12:00:14 by jiyunpar         ###   ########.fr       */
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

void	test_expand_wildcard(void)
{
	t_token	*token1;
	t_token	*token2;
	t_token	*token3;
	t_token	*token4;
	t_token	*token5;

	printf("\n====================all*==========================\n");
	token1 = make_token("'all*'", 2);
	expand_wildcard(token1);
	printf("%s\n", token1->value);
	printf("\n==============================================\n");
	token2 = make_token("*", 2);
	expand_wildcard(token2);
	printf("%s\n", token2->value);
	printf("\n==============================================\n");
	token3 = make_token("\"t*s*\"", 2);
	expand_wildcard(token3);
	printf("%s\n", token3->value);
	printf("\n==============================================\n");
	token4 = make_token(".h*", 2);
	expand_wildcard(token4);
	printf("%s\n", token4->value);
	printf("\n==============================================\n");
	token5 = make_token("*kefile", 2);
	expand_wildcard(token5);
	printf("%s\n", token5->value);
	free_token(token1);
	free_token(token2);
	free_token(token3);
	free_token(token4);
	free_token(token5);
}