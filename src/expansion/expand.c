/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 10:31:58 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/16 12:14:38 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
// expand()
// - 트리 순회 (트리에 있는 필드를 순회) -> 토큰
// 1. find metacharacter for expansion in field : $, *
// 2. if $, do env expand
// 3. if *, do filename expand

// void    expand_dollar(t_token *token)
// {
    
// }

// case: find *.c
// .:현재경로
// opendir() : 현재 디렉 토리 여는 거 
// readdir() ; 현잭 경로 디렉토피 파일
//
// *
// *asd
// asd*
// *asd*asdasd*
// *a*b*c*d*e*f
    // - asd
    // - gfhghasd
    // - gdhkfdasdfgdjkdfjkdf
    // *.c ->2case
// m*kefi*e -> makefile, m<hello>kfi<hello>e

// cat M*ke*

// k*ke* - wildcard
// khelslokehello - filename

// k**
// khel
// *이 아니라면 해당 문자가 있는지 본다. (해당 문자 없으면 끝)
// *이라면 *다음 문자가 있는지 본다. (다음 문자 만날 때까지 포인터 민다.)

// hello* -> hello* hellohello

bool	is_matchable_asterisk(char *dst_file, char *src_file)
{
    while (*dst_file || *src_file)
    {
        if (*src_file == '*')
        {
            while (*src_file == '*')
                ++src_file;
            dst_file = ft_strchr(dst_file, *src_file);
        }
		if (ft_strncmp(dst_file, src_file, 1) != 0)
            return (false);
		if (*dst_file)
  	    	++dst_file;
		if (*src_file)
    		++src_file;
    }
    return (true);
}

// void    expand_wildcard(t_token *token)
// {
//     DIR				*dirp;
//     struct dirent	*dp;

//     dirp = opendir(".");

//     while (dp = readdir(dirp))
//     {
//        if (is_matchable_asterisk(dp->d_name, token->value) == true)
// 	   {
//            free(token->value);
//            token->value = ft_strdup(dp->d_name);
//        }
//     }
// }


// void inoder_traverse()
// {
// 	if ()
// 		return ();
// 	inoder_traverse(left);
//     execute(tree_node);
// 	// expand();
// 	// redirect();
// 	// execute();
// 	inoder_traverse(right);
// }