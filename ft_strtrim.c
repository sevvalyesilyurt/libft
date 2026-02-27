/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/15 17:27:51 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/14 14:45:03 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		start;
	int		last;
	int		new_len;
	char	*new_str;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	last = ft_strlen((char *)s1) - 1;
	while (s1[start] != '\0' && ft_strchr(set, s1[start]))
		start++;
	while (s1[last] && ft_strchr(set, s1[last]))
		last--;
	new_len = last - start + 1;
	new_str = ft_substr(s1, (unsigned int)start, (size_t)new_len);
	return (new_str);
}
