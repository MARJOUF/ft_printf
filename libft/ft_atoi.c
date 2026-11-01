/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 09:51:24 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/27 13:55:27 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_chack_overflow(const char *nptr, long result, int sign, long i)
{
	long	check;

	check = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		check = (LONG_MAX - (nptr[i] - '0')) / 10;
		if (result > check)
		{
			if (sign < 0)
				return ((int)LONG_MIN);
			else
				return ((int)LONG_MAX);
		}
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *nptr)
{
	long	i;
	int		sign;
	long	result;

	result = 0;
	sign = 1;
	i = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	return (ft_chack_overflow(nptr, result, sign, i));
}
