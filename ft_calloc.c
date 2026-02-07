/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 16:34:51 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/07 04:35:33 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count != 0 && size > __SIZE_MAX__ / count)
		return (NULL);
	ptr = (void *) malloc(count * size);
	if (ptr == 0)
		return (NULL);
	ft_bzero(ptr, size * count);
	return (ptr);
}
