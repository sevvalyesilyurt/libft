/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 18:00:40 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 16:49:33 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memcpy(void *dest, const void *s, size_t n)
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
	return (dst);
}


#include <stdio.h>
int main()
{
	char arr[] = "aaaaaaaaaaaaaaaaaaa";
	char arr2[] = "bbbbbbbbb";
	int i = 0;
	ft_memcpy(arr, arr2,1);

	while (arr[i] != '\0')
	{
		printf("%c", arr[i]);
		i++;
	}
	
}
