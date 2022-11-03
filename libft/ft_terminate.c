/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_terminate.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:11:28 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/03 11:39:17 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_terminate(const char *str, int errno)
{
	const char	*err = strerror(errno);

	if (errno == 0)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd(err, 2);
	exit(1);
}
