/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_read_format.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/05 11:43:04 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/06 10:13:23 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

int	ft_read_format(const char *str, int *i, va_list *arg)
{
	t_bonus	g;

	ft_parse(str, i, &g);
	if (!str[*i])
	{
		(*i)--;
		return (0);
	}
	return (ft_format_bonus(&g, arg));
}
