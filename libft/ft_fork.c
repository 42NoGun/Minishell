/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fork.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 14:53:26 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 16:52:41 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_terminate("fork()");
	return (pid);
}
