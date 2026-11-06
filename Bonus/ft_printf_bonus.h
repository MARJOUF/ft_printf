/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/04 20:33:24 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/06 10:13:30 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_BONUS_H
# define FT_PRINTF_BONUS_H

#include <stdarg.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
	int		minus;
	int		zero;
	int		point;
	int		hashtag;
	int		space;
	int		plus;
	int		width;
	int		prec;
	char	specifier;
}	t_bonus;
int	ft_printf(const char *format, ...);
int	ft_read_format(const char *str, int *i, va_list *arg);
void	ft_parse(const char *s, int *i, t_bonus *g);
int ft_format_bonus(t_bonus *g, va_list *arg);
char	*ft_itoa(int n);
int	ft_putstr(char *s);
void ft_putspace(int c);
int	ft_putchar(char c);
int ft_strlen(char *s);

#endif