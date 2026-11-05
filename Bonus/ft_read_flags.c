/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:06:04 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/05 12:40:06 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void ft_flages_zero(t_bonus **a)
{
    (*a)->minus = 0;
    (*a)->zero = 0;
    (*a)->point = 0;
    (*a)->hashtag = 0;
    (*a)->space = 0;
    (*a)->plus = 0;
    (*a)->result = 0;
}

void ft_read_flags(const char *format, t_bonus *g)
{
    int i;

    i = 0;
    ft_flages_zero(&g);
    while (format[i])
    {
        if (format[i] == '-')
            g->minus = 1;
        else if (format[i] == '0')
            g->zero = 1;
        else if (format[i] == '.')
            g->point = 1;
        else if (format[i] == '#')
            g->hashtag = 1;
        else if (format[i] == ' ')
            g->space = 1;
        else if (format[i] == '+')
            g->plus = 1;
        i++;
    }
}
