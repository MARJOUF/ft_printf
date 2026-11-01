/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/17 08:37:36 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/30 15:42:44 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calcul_integers(int n)
{
	int	count;

	count = 0;
	if (n == INT_MIN)
	{
		count += 1;
		n = -147483648;
	}
	if (n < 0)
	{
		count += 1;
		n *= -1;
	}
	if (n == 0)
		count += 1;
	while (n > 0)
	{
		n /= 10;
		count += 1;
	}
	return (count);
}

static char	*ft_fill_the_array(int n, int count_argument, char *argument)
{
	while (n > 0)
	{
		argument[count_argument] = (n % 10) + '0';
		n /= 10;
		count_argument--;
	}
	return (argument);
}

char	*ft_itoa(int n)
{
	char	*argument;
	int		count_argument;

	count_argument = ft_calcul_integers(n);
	argument = malloc(count_argument + 1);
	if (argument == NULL)
		return (NULL);
	if (n == INT_MIN)
	{
		argument[1] = '2';
		n = -147483648;
	}
	if (n < 0)
	{
		argument[0] = '-';
		n *= -1;
	}
	if (n == 0)
		argument[0] = '0';
	argument[count_argument--] = '\0';
	return (ft_fill_the_array(n, count_argument, argument));
}
