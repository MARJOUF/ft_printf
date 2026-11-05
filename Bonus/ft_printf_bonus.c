/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 20:34:34 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/05 15:07:06 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static int ft_error(va_list *arg)
{
    va_end(*arg);
    return (-1);
}

int ft_printf_bonus(const char *format, ...)
{
    va_list arg;
    int i;
    int se;
    int count;

    count = 0;
    i = 0;
    va_start(arg, format);
    while (format[i] != '%' && format[i + 1])
    {
        count += ft_putchar(format[i]);
        i++;
    }
    while (format[i] == '%' && format[i + 1])
    {
        se = ft_read_format(format, i + 1, &arg);
        i++;
    }
    if (se == -1)
        return (ft_error(&arg));
    count += se;
    return (count);
}
