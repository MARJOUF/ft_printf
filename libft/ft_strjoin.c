/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/14 19:45:16 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/15 14:25:01 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_strcat(char *arr, char *s1, char *s2)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = 0;
	if (s1 && s2)
	{
		while (s1[i])
			arr[j++] = s1[i++];
		i = 0;
		while (s2[i])
			arr[j++] = s2[i++];
	}
	else if (!s2)
	{
		while (s1[i])
			arr[j++] = s1[i++];
	}
	else
	{
		while (s2[i])
			arr[j++] = s2[i++];
	}
	arr[j] = '\0';
	return (arr);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*arr;
	size_t	len_s1;
	size_t	len_s2;
	size_t	size;

	len_s1 = 0;
	len_s2 = 0;
	if (!s1 && !s2)
		return (NULL);
	if (s1)
		len_s1 = ft_strlen(s1);
	if (s2)
		len_s2 = ft_strlen(s2);
	size = len_s1 + len_s2;
	arr = malloc(size + 1);
	if (arr == NULL)
		return (NULL);
	ft_strcat(arr, (char *)s1, (char *)s2);
	return (arr);
}
