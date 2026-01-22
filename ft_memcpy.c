/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:00:40 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/09 15:58:59 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	ft_memcpy(void *s, const void *dest, size_t n)
{
	unsigned int	i;
	unsigned char	*str;
	unsigned char	*dst;

	str = (unsigned char *) s;
	dst = (unsigned char *)dest;
	i = 0;
	while (n)
	{
		dst[i] = str[i];
		i++;
		n--;
	}
}
