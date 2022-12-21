/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:56:04 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 15:08:13 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int	_chdir(char *path)
{
	int	ret;

	ret = chdir(path);
	if (ret == 0)
		return (0);
	else
	{
		perror("cd");
		return (1);
	}
}
