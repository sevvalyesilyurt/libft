/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:22:22 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 13:27:39 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(char c)
{
	if ((c <= 90 && c >= 65) || (c <= 122 && c >= 97))
		return (1);
	return (0);
}

#include <stdio.h>
int main()
{
	printf("%d", ft_isalpha('2')); //0T
	printf("%d", ft_isalpha('a'));//1T
	printf("%d", ft_isalpha(','));//0T
	printf("%d", ft_isalpha('A'));//1T
}