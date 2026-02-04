/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sevyesil <sevyesil@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 11:44:00 by sevyesil          #+#    #+#             */
/*   Updated: 2026/02/03 13:22:57 by sevyesil         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*temp;
	void	*node;

	temp = NULL;
	if (!lst || !f || !del)
		return (NULL);
	while (lst)
	{
		node = lst->content;
		f(&node);
		if (!node)
		{
			ft_lstclear(&temp, del);
			del(&lst);
			return (NULL);
		}
		else
		{
			ft_lstadd_back(&temp, node);
		}
		lst = lst->next;
	}
	return (temp);
}
