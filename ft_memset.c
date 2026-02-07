/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:40:57 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/07 01:37:22 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	b;
	unsigned char	*p;

	b = (unsigned char) c;
	p = (unsigned char *)s;
	while (n)
	{
		*p++ = b;
		n--;
	}
	return (p);
}
