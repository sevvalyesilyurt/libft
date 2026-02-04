/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:40:57 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 15:08:41 by sevyesil         ###   ########.fr       */
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

#include <stdio.h>
int main()
{
	char arr[2];
	int i = 0;
	
	ft_memset(arr, 'B',3);
	
	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
}
