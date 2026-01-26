/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/22 18:47:42 by sevyesil          #+#    #+#             */
/*   Updated: 2026/01/22 19:52:08 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

#include <stdlib.h>

static char	*putnbr_rec(long n, char *str)
{
	if (n > 9)
		str = putnbr_rec(n / 10, str);
	*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	char	*start;
	long	nb;
	int		len;

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
	if (!str)
		return (NULL);
	start = str;
	if (nb < 0)
	{
		*str++ = '-';
		nb = -nb;
	}
	str = putnbr_rec(nb, str);
	*str = '\0';
	return (start);
}

#include <unistd.h>
int main()
{
	char	*str;
	int		i;

	i = 0;
	str = ft_itoa(2345);

	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
}
