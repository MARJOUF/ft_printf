/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/13 13:50:15 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/27 13:58:13 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	a;
	size_t	count;
	size_t	src_len;

	src_len = ft_strlen(src);
	a = 0;
	i = 0;
	while (i < size && dest[i])
		i++;
	if (i == size)
		return (size + src_len);
	count = i;
	while (src[a] && i < size - 1)
	{
		dest[i] = src[a];
		i++;
		a++;
	}
	dest[i] = '\0';
	return (count + src_len);
}
