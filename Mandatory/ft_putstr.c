/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 18:43:22 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/04 13:08:51 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putstr(char *s)
{
	size_t	tool;

	if (!s)
		return (write(1, "(null)", 6));
	tool = ft_strlen(s);
	if (write(1, s, tool) == -1)
		return (-1);
	return (tool);
}
