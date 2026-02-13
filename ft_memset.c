/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:40:57 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/10 21:26:46 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	b;
	unsigned char	*p;
	size_t			i;

	i = 0;
	b = (unsigned char) c;
	p = (unsigned char *)s;
	while (i < n)
	{
		p[i] = b;
		i++;
	}
	return (p);
}
