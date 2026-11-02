/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/30 16:22:20 by akmarjou          #+#    #+#             */
/*   Updated: 2026/11/02 14:52:35 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int ft_printf(const char *str, ...);
int ft_format_handel(const char *str, int i, va_list *arg);
void ft_base(void *a,int *count);
int	ft_putchar(char c);
int	ft_putstr(char *s);
char	*ft_itoaf(unsigned int n);

#endif 
