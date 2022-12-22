/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dup2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:00:33 by cheseo            #+#    #+#             */
/*   Updated: 2022/12/22 14:00:43 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	_dup2(int fildes, int fildes2)
{
	int	ret;

	ret = dup2(fildes, fildes2);
	if (ret == -1)
		ft_terminate("dup2");
	return (ret);
}
