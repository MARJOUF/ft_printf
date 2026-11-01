/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:22:20 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/01 18:44:32 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int ft_printf(const char *str, ...);
int ft_format_handel(const char *str, int i, va_list *arg);
void ft_base(void *a);
int	ft_putchar(char c);
int	ft_putstr(char *s);

#endif 
