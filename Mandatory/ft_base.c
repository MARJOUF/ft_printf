/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:50:35 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/01 19:19:25 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void ft_base(void *a)
{
    char *base;
    unsigned long p;
    
    base = "0123456789abcdef";
    p = (unsigned long)a;
    if (p >= 16)
    {
        ft_base((void *)(p / 16));
    }
    ft_putchar_fd(base[p % 16], 1);
}