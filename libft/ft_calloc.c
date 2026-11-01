/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 10:58:17 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/29 14:33:42 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*arr;
	size_t	reslt;

	if (size != 0 && nmemb > (size_t)-1 / size)
		return (NULL);
	reslt = nmemb * size;
	if (reslt == 0)
		return (malloc(1));
	arr = malloc(reslt);
	if (arr == NULL)
		return (NULL);
	ft_bzero(arr, reslt);
	return (arr);
}
