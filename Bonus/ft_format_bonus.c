/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 14:25:50 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/05 15:26:56 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int ft_format_bonus(t_bonus *g, va_list *arg)
{
    int count;

    count = 0;
    if (g->specifier == 'd' || g->specifier == 'i')
    {
        count += ft_format_minus(g, arg);
        printf("\ncount: %d\n", count);
    }
    return (count);
}
