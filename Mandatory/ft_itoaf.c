/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoaf.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/02 14:50:37 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/08 14:04:26 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static unsigned int	ft_calcul_integers(unsigned int n)
{
	unsigned int	count;

	count = 0;
	if (n == 0)
		count += 1;
	while (n > 0)
	{
		n /= 10;
		count += 1;
	}
	return (count);
}

static char	*ft_fill_the_array(unsigned int n, unsigned int count_argument,
		char *argument)
{
	while (n > 0)
	{
		argument[count_argument] = (n % 10) + '0';
		n /= 10;
		count_argument--;
	}
	return (argument);
}

char	*ft_itoaf(unsigned int n)
{
	char			*argument;
	unsigned int	count_argument;

	count_argument = ft_calcul_integers(n);
	argument = malloc(count_argument + 1);
	if (argument == NULL)
		return (NULL);
	if (n == 0)
		argument[0] = '0';
	argument[count_argument--] = '\0';
	return (ft_fill_the_array(n, count_argument, argument));
}
