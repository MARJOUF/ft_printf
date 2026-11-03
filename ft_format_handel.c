/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format_handel.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/31 11:08:32 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/03 20:50:05 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_nmbr_lowupp(const char *str, int i, va_list **arg)
{
	unsigned int	c;
	int				count_nmbr;
	char			*st;

	count_nmbr = 0;
	if (str[i] == 'u')
	{
		c = va_arg(**arg, unsigned int);
		st = ft_itoaf(c);
		ft_putstr(st);
		count_nmbr += ft_strlen(st);
		free(st);
	}
	else if (str[i] == 'x' || str[i] == 'X')
	{
		c = va_arg(**arg, unsigned int);
		ft_base_x(str, i, c, &count_nmbr);
	}
	return (count_nmbr);
}
static int	ft_nmbr_address(const char *str, int i, va_list **arg)
{
	int		c;
	void	*a;
	char	*st;
	int		count_nmbr;

	count_nmbr = 0;
	if (str[i] == 'd' || str[i] == 'i')
	{
		c = va_arg(**arg, int);
		st = ft_itoa(c);
		ft_putstr(st);
		count_nmbr += ft_strlen(st);
		free(st);
	}
	else if (str[i] == 'p')
	{
		a = va_arg(**arg, void *);
		if (a != NULL)
			count_nmbr += ft_putstr("0x");
		ft_base(a, &count_nmbr);
	}
	return (count_nmbr);
}

static int	ft_strchrstr(const char *str, int i, va_list **arg)
{
	int		count;
	char	*string;
	int		c;

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
		count += ft_putstr(string);
	}
	return (count);
}
int	ft_format_handel(const char *str, int i, va_list *arg)
{
	int	count_nmbr;

	count_nmbr = 0;
	if (str[i] == 'c' || str[i] == 's')
		count_nmbr += ft_strchrstr(str, i, &arg);
	else if (str[i] == 'd' || str[i] == 'p' || str[i] == 'i')
		count_nmbr += ft_nmbr_address(str, i, &arg);
	else if (str[i] == 'u' || str[i] == 'x' || str[i] == 'X')
		count_nmbr += ft_nmbr_lowupp(str, i, &arg);
	else if (str[i] == '%')
		count_nmbr += ft_putchar('%');
	return (count_nmbr);
}
