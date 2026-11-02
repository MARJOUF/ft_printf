/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 18:43:22 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/02 10:11:49 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int ft_putstr(char *s)
{
    size_t tool;

    if (!s)
        return (0);
    tool = ft_strlen(s);
    if (write(1, s, tool) == -1)
        return (-1);
    return (tool);
}