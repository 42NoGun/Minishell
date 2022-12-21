/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 15:07:10 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/12/21 15:48:35 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

int	_pipe(int **fildes)
{
	int	ret;

	ret = pipe(*fildes);
	if (ret == -1)
		ft_terminate("pipe");
	return (0);
}
