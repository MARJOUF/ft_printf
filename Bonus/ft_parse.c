/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/06 10:11:30 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/06 10:17:53 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf_bonus.h"

static void	ft_init_bonus(t_bonus *g)
{
	g->minus = 0;
	g->zero = 0;
	g->point = 0;
	g->hashtag = 0;
	g->space = 0;
	g->plus = 0;
	g->width = 0;
	g->prec = 0;
	g->specifier = 0;
}

static void	ft_set_flag(char c, t_bonus *g)
{
	if (c == '-')
		g->minus = 1;
	else if (c == '0')
		g->zero = 1;
	else if (c == '#')
		g->hashtag = 1;
	else if (c == '+')
		g->plus = 1;
	else if (c == ' ')
		g->space = 1;
}

static void	ft_fix_flags(t_bonus *g)
{
	if (g->minus)
		g->zero = 0;
	if (g->plus)
		g->space = 0;
}

static void	ft_parse_prec(const char *s, int *i, t_bonus *g)
{
	if (s[*i] != '.')
		return ;
	g->point = 1;
	(*i)++;
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		g->prec = g->prec * 10 + (s[*i] - '0');
		(*i)++;
	}
}

void	ft_parse(const char *s, int *i, t_bonus *g)
{
	ft_init_bonus(g);
	while (s[*i] == '-' || s[*i] == '0' || s[*i] == '#'
		|| s[*i] == '+' || s[*i] == ' ')
	{
		ft_set_flag(s[*i], g);
		(*i)++;
	}
	while (s[*i] >= '0' && s[*i] <= '9')
	{
		g->width = g->width * 10 + (s[*i] - '0');
		(*i)++;
	}
	ft_parse_prec(s, i, g);
	ft_fix_flags(g);
	g->specifier = s[*i];
}
