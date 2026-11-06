/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 20:34:34 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/06 10:12:46 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int ft_error(va_list *arg)
{
    va_end(*arg);
    return (-1);
}

int	ft_printf(const char *format, ...)
{
	va_list	arg;
	int		i;
	int		count;
	int		se;

	i = 0;
	count = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			i++;
			se = ft_read_format(format, &i, &arg);
		}
		else
			se = ft_putchar(format[i]);
		if (se == -1)
			return (ft_error(&arg));
		count += se;
		i++;
	}
	va_end(arg);
	return (count);
}
