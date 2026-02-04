/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 18:20:04 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 18:19:30 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s++ == (char) c)
		{
			return ((char *)s);
		}
	}
	if (*s == (char)c)
	{
		return ((char *)s);
	}
	return (0);
}

#include <stdio.h>

int main()
{
	char *ss = "hsdhfahAAdsfh";
	char *temp;
	temp = ft_strchr(ss, 65);
	
	printf("%s",temp);
}