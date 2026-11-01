/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akmarjou <akmarjou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/10/16 13:55:24 by akmarjou          #+#    #+#             */
/*   Updated: 2026/10/30 15:43:58 by akmarjou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_calcul_count_of_character(char const *s, char c)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (s[i] && s[i] != c)
	{
		count += 1;
		i++;
	}
	return (count);
}

static int	ft_calcul_first_character_in_the_words(char const *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count += 1;
		i++;
	}
	return (count);
}

static char	*ft_fill_the_arrays(char const *s, int len_s)
{
	char	*string;
	int		i;

	i = 0;
	string = malloc(len_s + 1);
	if (string == NULL)
	{
		return (NULL);
	}
	while (i < len_s)
	{
		string[i] = s[i];
		i++;
	}
	string[i] = '\0';
	return (string);
}

static char	**ft_chaeck_all_done_and_free(int count_words, char c,
		char const *s, char **array)
{
	int	len_s;
	int	pos;
	int	i;

	i = 0;
	len_s = 0;
	pos = 0;
	while (i < count_words)
	{
		pos += len_s;
		while (s[pos] == c)
			pos++;
		len_s = ft_calcul_count_of_character(s + pos, c);
		array[i] = ft_fill_the_arrays(s + pos, len_s);
		if (array[i] == NULL)
		{
			while (i > 0)
				free(array[--i]);
			free(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;
	int		count_words;

	if (!s)
		return (NULL);
	count_words = ft_calcul_first_character_in_the_words(s, c);
	array = malloc((count_words + 1) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	return (ft_chaeck_all_done_and_free(count_words, c, s, array));
}
