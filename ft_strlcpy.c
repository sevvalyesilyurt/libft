/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/05 16:00:08 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 17:53:07 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned int	ft_strlcpy(char *dest, char *src, unsigned int size)
{
	unsigned int	i;
	unsigned int	len;

	len = 0;
	i = 0;
	while (src[len] != '\0')
	{
		++len;
	}
	if (len == 0)
	{
		return (len);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest [i] = '\0';
	return (len);
}

#include <stdio.h>
int main()
{
	char arr[] = "aaaaaaaaaaaaaaaaaaa";
	char arr2[] = "bbbbbbbbb";
	int i = 0;
	ft_strlcpy(arr, arr2,3);

	
		printf("%d", ft_strlcpy(arr, arr2,3));
	
	
}

