/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:00:34 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 16:08:12 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

ssize_t	_write(int fildes, const void *buf, size_t nbyte)
{
	ssize_t	ret;

	ret = write(fildes, buf, nbyte);
	if (ret == -1)
		ft_terminate("write()");
	return (ret);
}
