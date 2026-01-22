/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 16:04:39 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/15 17:26:33 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;

	i = 0;
	str = (char *) malloc(1 + ft_strlen((char *)s1) + ft_strlen((char *)s2));
	if (!str)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = *s1++;
	}
	while (s2[i] != '\0')
	{
		str[i] = *s2++;
	}
	str[i] = '\0';
	return (str);
}
