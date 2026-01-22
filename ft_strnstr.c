/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:31:10 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/22 15:14:11 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strnstr(char *big_s1, char *little_s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	j = 0;
	i = 0;
	little_len = ft_strlen(little_s2);
	if (little_s2[0] == '\0')
		return (little_s2);
	if (len < little_len)
		return (0);

	while (big_s1[i] != '\0')
	{
		j = 0;
		while (big_s1[i + j] == little_s2[j] && little_s2[j] != '\0')
		{
			j++;
		}
		if (little_s2[j] == '\0')
			return (&big_s1[i]);
		i++;
	}
	return (0);
}
