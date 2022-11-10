/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_read_quote_content.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:20:20 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/10 17:16:22 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "test.h"
#include <stdio.h>

void    test_read_quote_content(void)
{
    char    *str1;
    char    *str2;

    str1 = strdup("\"Hello\"World");
	str2 = strdup("\"\"a\"\"");
	// printf("ex: %s\n", read_quote_content(&str2));

    ft_assert(ft_strcmp(read_quote_content(&str1, '\"'), "\"Hello\""), 0, "read_quote_content : 22");
    ft_assert(ft_strcmp(read_quote_content(&str2, '\"'), "\"\""), 0, "read_quote_content : 23");
}
