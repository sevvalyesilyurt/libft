/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:27:51 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/15 18:21:21 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		len;
	char	*str;
	char	*dest;

	len = ft_strlen((char *)s1);
	while (!set)
	{
		if (s1[0] == *set++)
			len--;
		else if (s1[len - 1] == *set++)
			len--;
	}
	str = (char *) malloc(len + 1);
	while
}
