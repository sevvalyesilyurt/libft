/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/09 19:27:35 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/07 03:08:26 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

char	*ft_strrchr(const char *s, int c)
{
	char	*last;

	last = 0;
	while (*s)
	{
		if (*s == (char) c)
		{
			last = (char *)s;
		}
		s++;
	}
	if (*s == (char) c)
	{
		return ((char *)s);
	}
	return (last);
}
