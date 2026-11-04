/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_base.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/01 15:50:35 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/04 12:48:15 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_base(void *a, int *count)
{
	char			*base;
	unsigned long	p;
	int				se;

	se = 0;
	base = "0123456789abcdef";
	if (!a)
	{
		se = ft_putstr("(nil)");
		if (se == -1)
			return ;
		*count += se;
		return ;
	}
	p = (unsigned long)a;
	if (p >= 16)
		ft_base((void *)(p / 16), count);
	se = ft_putchar(base[p % 16]);
	if (se == -1)
		return ;
	*count += se;
}

void	ft_base_x(const char *str, int i, unsigned int p, int *count)
{
	char	*base;
	int		se;

	se = 0;
	if (str[i] == 'x')
		base = "0123456789abcdef";
	if (str[i] == 'X')
		base = "0123456789ABCDEF";
	if (p >= 16)
		ft_base_x((void *)str, i, (p / 16), count);
	se += ft_putchar(base[p % 16]);
	if (se == -1)
		return ;
	*count += se;
}
