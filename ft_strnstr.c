/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:31:10 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/08 16:08:51 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big_s1, const char *little_s2, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	little_len;

	j = 0;
	i = 0;
	little_len = ft_strlen(little_s2);
	if (little_s2[0] == '\0')
		return ((char *)little_s2);
	if (len < little_len)
		return (0);
	while (big_s1[i] != '\0' && i < len)
	{
		j = 0;
		while (big_s1[i + j] == little_s2[j] && little_s2[j] != '\0'
			&& i + j < len)
		{
			j++;
		}
		if (little_s2[j] == '\0')
			return ((char *)&big_s1[i]);
		i++;
	}
	return (0);
}
