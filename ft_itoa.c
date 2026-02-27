/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:47:42 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/14 15:32:30 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*putnbr_rec(long n, char *str)
{
	if (n < 0)
		n = -n;
	if (n > 9)
		str = putnbr_rec(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	long	nb;
	int		len;
	char	*start;

	nb = n;
	len = 0;
	if (nb <= 0)
		len = 1;
	while (n)
	{
		n = n / 10;
		len++;
	}
	str = (char *)malloc(len + 1);
	start = str;
	if (!str)
		return (NULL);
	if (nb < 0)
	{
		*str++ = '-';
	}
	str = putnbr_rec(nb, str);
	*str++ = '\0';
	return (start);
}
