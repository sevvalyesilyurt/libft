/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 15:03:40 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/22 18:10:44 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	**str_add(unsigned char *str, char **dest, char c)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i - 1] == c && str[i + 1] != c)
		{
			j = 0;
			while (str[i] == c)
			{
				*dest[j] = str[i];
				i++;
				j++;
			}
			dest++;
		}
		else
			i++;
	}
	return (dest);
}

char	**ft_split(char const *s, char c)
{
	unsigned char	*str;
	int				i;
	int				j;
	char			**split_str;

	i = 0;
	j = 0;
	str = (unsigned char *)s;
	while (str[i])
	{
		if (str[0] == c)
		{
		}
		if (str[i] == c && str[i + 1] != c && str[i + 1] != '\0')
			j++;
		i++;
	}
	split_str = (char **)malloc(j + 1 * sizeof(char *));
	if (!split_str)
		return (NULL);
	split_str = str_add(str, split_str, c);
	return (split_str);
}
