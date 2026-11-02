/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:50:35 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/02 12:17:32 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void ft_base(void *a, int *count)
{
    char *base;
    unsigned long p;
    
    base = "0123456789abcdef";
    p = (unsigned long)a;
    if (p >= 16)
        ft_base((void *)(p / 16),count);
    *count += ft_putchar(base[p % 16]);
}