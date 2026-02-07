/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 15:54:27 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/07 03:01:41 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char		*d;
	char		*s;
	char		*lasts;
	char		*lastd;

	if (!src || !dest)
		return (NULL);
	d = (char *)dest;
	s = (char *)src;
	if (d < s)
	{
		while (n)
		{
			*d++ = *s++;
			n--;
		}
	}
	else
	{
		lasts = s + (n - 1);
		lastd = d + (n - 1);
		while (n--)
			*lastd-- = *lasts--;
	}
	return (dest);
}
