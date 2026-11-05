/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ato_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:47:42 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/05 14:15:58 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int ft_ato_bonus(const char *str, int i)
{
    int result;
    int count;

    count = 0;
    result = 0;
    while (str[i] == '-' || str[i] == '+' || str[i] == '0' || str[i] == '.' ||
        str[i] == '#' || str[i] == ' ')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        result = (result * 10) + (str[i] - '0');
        i++;
    }
    while (str[i] == '-' || str[i] == '+' || str[i] == '0' || str[i] == '.' ||
        str[i] == '#' || str[i] == ' ')
        i++;
    while (str[i] >= '0' && str[i] <= '9')
    {
        count = (count * 10) + (str[i] - '0');
        i++;
    }
    if (count > result)
        return (count);
    return (result);
}
