/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:43:04 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/05 15:01:06 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void ft_read_specifier(const char *str, int i, t_bonus *g)
{
    int count_nmbr;

    count_nmbr = 0;
    while (str[i] && str[i] != 'c' && str[i] != 's' && str[i] != 'p' &&
        str[i] != 'd' && str[i] != 'i' && str[i] != 'u' &&
        str[i] != 'x' && str[i] != 'X' && str[i] != '%')
        i++;
    g->specifier = str[i];
    
}

int ft_read_format(const char *str, int i, va_list *arg)
{
    (void)arg;
    const char *str2;
    int count;
    int result;
    t_bonus g;
    
    result = 0;
    count = 0;
    str2 = str;
    ft_read_flags(str2, &g);
    g.result += ft_ato_bonus(str, i);
    ft_read_specifier(str, i, &g);
    count += ft_format_bonus(&g, arg);
    return (count);
}
