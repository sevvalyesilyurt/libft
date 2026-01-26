/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 16:44:48 by marvin            #+#    #+#             */
/*   Updated: 2026/01/25 16:44:48 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <libft.h>

void ft_putnbr_fd(int n, int fd)
{
    char *str;
    int     i;

    i = 0;
    str = ft_itoa(n);
    if (!str)
        return;
    while (str[i])
    {
        write(fd, &str[i], 1);
        i++;
    }
    free(str);
}
