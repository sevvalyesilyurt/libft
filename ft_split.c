/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:03:40 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/13 17:27:30 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	word_len(unsigned char *str, int i, char c)
{
	int	len;

	len = 0;
	while (str[i] && str[i] != c)
	{
		len++;
		i++;
	}
	return (len);
}

char	**str_add(unsigned char *str, char **dest, char c)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			k = 0;
			dest[j] = (char *)malloc(word_len(str, i, c) + 1);
			if (!dest[j])
				return (NULL);
			while (str[i] && str[i] != c)
				dest[j][k++] = str[i++];
			dest[j][k] = '\0';
			j++;
		}
		else
			i++;
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

#include <stdio.h>

#include <string.h>
int main(int argc, char const *argv[])
{
	char *str = strdup("hxello.sevval");
	char c = '.';

	int j;
	j = 0;
	char **str_free = ft_split(str, c);
	
	while (str_free[j])
	{
		printf("%s \n", str_free[j]);
		j++;
	}
	
	free(str_free);
	return 0;
}
