/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:29:06 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/04 17:57:25 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_error(va_list *arg)
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
	se = 0;
	va_start(arg, format);
	while (format[i])
	{
		if (format[i] == '%' && format[i + 1])
		{
			se = ft_format_handel(format, i + 1, &arg);
			i++;
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
