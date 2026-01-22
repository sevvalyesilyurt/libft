/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/14 12:05:30 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/15 18:28:42 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"


char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new_str;
	char	*str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	str = (char *) s;
	if ((int) start >= ft_strlen((char *)s))
	{
		new_str = ft_memset(s, 32, 1);
		return (new_str);
	}
	if (len > ft_strlen((char *)s) - start)
		len = ft_strlen((char *)s) - start;
	new_str = (char *)malloc(len + 1);
	if (!new_str)
		return (NULL);
	while (len-- && s[start + i] != '\0')
	{
		new_str[i] = str[start + i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}
