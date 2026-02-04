/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:38:44 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 13:38:31 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(char c)
{
	if (c <= 126 && c >= 32)
	{
		return (1);
	}
	return (0);
}
#include <stdio.h>
int main()
{
	printf("%d", ft_isprint(12)); //0T
	printf("%d", ft_isprint('	'));//0T
	printf("%d", ft_isprint(' '));//1T
	printf("%d", ft_isprint('A'));//1T
}