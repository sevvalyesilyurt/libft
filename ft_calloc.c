/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:34:51 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/13 17:49:11 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft_a.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count * size > __SIZE_MAX__)
		return (NULL);
	ptr = (void *) malloc(count * size);
	if (ptr == 0)
		return (NULL);
	bzero(ptr, size * count);
	return (ptr);
}
