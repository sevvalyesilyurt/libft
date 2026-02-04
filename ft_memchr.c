/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/10 15:17:44 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 19:46:55 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t				i;
	const unsigned char	*memory;

	memory = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (memory[i] == (unsigned char) c)
		{
			return ((void *)(memory + i));
		}
		i++;
	}
	return (NULL);
}
#include <stdio.h>
int main()
{
	int 	s1 = 12345;
	char	*temp;

	temp = (char *)ft_memchr(&s1, 56, 2);
	printf("%p",temp);
}
