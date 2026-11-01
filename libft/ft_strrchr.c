/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 15:31:06 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/20 10:12:44 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*a;

	a = s;
	while (*s)
		s++;
	if (c == '\0')
		return ((char *)s);
	if (s == a)
		return (NULL);
	s--;
	while (s > a)
	{
		if (*s == (char)c)
			return ((char *)s);
		s--;
	}
	if (*a == (char)c)
		return ((char *)a);
	return (NULL);
}
