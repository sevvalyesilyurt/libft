/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/08 16:27:49 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 13:29:12 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(char c)
{
	if (c <= '9' && c >= '0')
	{
		return (1);
	}
	return (0);
}
#include <stdio.h>
int main()
{
	printf("%d", ft_isdigit('2')); //1T
	printf("%d", ft_isdigit('a'));//0T
	printf("%d", ft_isdigit(','));//0T
	printf("%d", ft_isdigit('A'));//0T
}
