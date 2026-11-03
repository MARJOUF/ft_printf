/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/03 15:29:06 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/03 15:48:14 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int ft_printf(const char *str, ...)
{
    va_list arg;    
    int i;
    int count;
    int se;

    i = 0;
    count = 0;
    se = 0;
    va_start(arg, str);
    while (str[i])
    {
        if (str[i] == '%' && str[i + 1])
        {
            se = ft_format_handel(str, i + 1, &arg);
            if (se == -1)
                break;
            count += se; 
            i++;
        }
        else 
        {
            se = ft_putchar(str[i]);
            if(se == -1)
                break;
            count += se;
        }
        i++;
    }
    va_end(arg);
    if (se == -1)
        return (-1);
    return (count);
}