/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:27:51 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/04 19:03:58 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		s1_len;
	char	*str;

	i = 0;
	s1_len = ft_strlen((char *)s1);
	j = s1_len;
	while (*s1++)
	{
		while (*set++)
		{
			if (*s1 == *set)
				i++;
		}
	}
	while (*s1--)
	{
		while (*set++)
		{
			if (*s1 == *set)
				j--;
		}
	}
	str = ft_substr(s1, i, s1_len - i);
	return (str);
}
