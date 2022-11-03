/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 12:11:28 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/11/02 12:17:37 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	terminate(const char *str, int errno)
{
	const char	*err = strerror(errno);

	if (errno == 0)
	{
		wrtie(2, str, ft_strlen(str));
		exit(1);
	}
	else
		write(2, err, ft_strlen(err));
}
