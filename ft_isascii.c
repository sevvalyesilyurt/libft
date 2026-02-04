/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:34:36 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 13:34:30 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii( char c)
{
	if (c <= 127 && c >= 0)
	{
		return (1);
	}
	return (0);
}
#include <stdio.h>
int main()
{
	printf("%d", ft_isascii(-127)); //0T
	printf("%d", ft_isascii('a'));//1T
	printf("%d",ft_isascii(','));//1T
	printf("%d",ft_isascii(-16));//0T
}