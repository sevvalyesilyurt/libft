/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:05:30 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/14 14:45:17 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t			i;
	unsigned char	*str;
	char			*new_str;

	if (!s)
		return (NULL);
	str = (unsigned char *) s;
	if (!str)
		return (NULL);
	if (start >= ft_strlen((char *)str))
		return (ft_strdup(""));
	if (len > ft_strlen((char *)str) - start)
		len = ft_strlen((char *)str) - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
