/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:03:40 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/17 04:40:44 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_len(const unsigned char *str, char c)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	return (len);
}

static void	free_split(char **dest, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(dest[i]);
		i++;
	}
	free(dest);
}

static char	**str_add(const unsigned char *str, char **dest, char c)
{
	int	j;
	int	k;

	j = 0;
	while (*str)
	{
		if (*str == c)
			str++;
		else
		{
			k = 0;
			dest[j] = (char *)malloc(word_len(str, c) + 1);
			if (!dest[j])
			{
				free_split(dest, j);
				return (NULL);
			}
			while (*str && *str != c)
				dest[j][k++] = *str++;
			dest[j][k] = '\0';
			j++;
		}
	}
	dest[j] = NULL;
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	unsigned char	*str;
	int				i;
	int				words;
	char			**split_str;

	if (!s)
		return (NULL);
	str = (unsigned char *)s;
	i = 0;
	words = 0;
	while (str[i])
	{
		if (str[i] != c && (i == 0 || str[i - 1] == c))
			words++;
		i++;
	}
	split_str = (char **)malloc((words + 1) * sizeof(char *));
	if (!split_str)
		return (NULL);
	return (str_add(str, split_str, c));
}
