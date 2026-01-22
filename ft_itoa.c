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

char	*ft_putstr(int n, char *str)
{
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		n = (long) n;
	}
	if (n < 0)
		n = -n;
	if (n > 9)
	{
		ft_putstr(n / 10, str);
		*str++ = (n % 10) + '0';
	}
	else
		*str++ = (n % 10) + '0';
	return (str);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 0;
	while (n > 9 || n < -9)
	{
		n = n / 10;
		i++;
	}
	str = (char *)malloc(i + 1);
	return (ft_putstr(n, str));
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
