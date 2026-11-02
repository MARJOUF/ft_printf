/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_handel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 11:08:32 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/02 12:17:46 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

static int ft_nmbr_address(const char *str, int i, va_list **arg)
{
    int c;
    void *a;
    char *st;
    int base;
    int count_nmbr;
    
    count_nmbr = 0;
    base = 0;
    if (str[i] == 'd' || str[i] == 'i')
    {
        c = va_arg(**arg, int);
        st = ft_itoa(c);
        ft_putstr(st);
        count_nmbr += ft_strlen(st);
    }
    else if (str[i] == 'p')
    {
        a = va_arg(**arg, void *);
        base += write(1, "0x", 2);
        ft_base(a, &count_nmbr);
    }
    return (count_nmbr + base);
}

static int ft_strchrstr(const char *str, int i, va_list **arg)
{
    int count;
    char *string;
    int c;

    count = 0;
    if (str[i] == 'c')
    {
        c = va_arg(**arg, int);
        ft_putchar(c);
        count++;
    }
    else if (str[i] == 's')
    {
        string = va_arg(**arg, char *);
        ft_putstr(string);
        count += ft_strlen(string);
    }
    return (count);
}
int    ft_format_handel(const char *str, int i, va_list *arg)
{
    int c;
    int count_str;
    int count_nmbr;
    int *a;
    
    count_str = 0;
    count_nmbr = 0;
    if (str[i] == 'c' || str[i] == 's')
        count_str += ft_strchrstr(str, i, &arg);
    else if (str[i] == 'd' || str[i] == 'p' || str[i] == 'i')
        count_nmbr += ft_nmbr_address(str, i, &arg);
    return (count_str + count_nmbr);
}
