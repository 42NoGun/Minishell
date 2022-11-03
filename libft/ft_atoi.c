/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiyunpar <jiyunpar@student.42seou.kr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/13 17:39:21 by jiyunpar          #+#    #+#             */
/*   Updated: 2022/08/26 13:17:10 by jiyunpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	check_long_max(const char *str, long value, int sign, int index)
{
	if ((value > 922337203685477580 || (value == 922337203685477580 \
	&& (str[index] - '0') > 7)) && sign == 1)
		return (-1);
	else if ((value > 922337203685477580 || (value == 922337203685477580 \
	&& (str[index] - '0') > 8)) && sign == -1)
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int		sign;	
	long	value;
	int		i;

	sign = 1;
	value = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (check_long_max(str, value, sign, i) == -1)
			return (-1);
		else if (check_long_max(str, value, sign, i) == 0)
			return (0);
		value = value * 10 + (str[i] - '0');
		i++;
	}
	return ((int)(value * sign));
}
