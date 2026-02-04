/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:27:35 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 18:25:10 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	while (*s)
	{
		if (*s == (char) c)
		{
			last = s;
		}
		s++;
	}
	if (*s == (char) c)
	{
		return ((char *)s);
	}
	return ((char *)last);
}

#include <stdio.h>

int main()
{
	char *ss = "hsdhfahAAdsfh";
	char *temp;
	temp = ft_strrchr(ss, 104);
	
	printf("%s",temp);
}