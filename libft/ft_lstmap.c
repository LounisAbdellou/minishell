/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 11:18:06 by labdello          #+#    #+#             */
/*   Updated: 2024/05/29 16:42:50 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*front;
	void	*content;

	if (!lst || !f || !del)
		return (NULL);
	front = 0;
	while (lst != NULL)
	{
		content = f(lst->content);
		new = ft_lstnew(content);
		if (!new)
		{
			del(content);
			ft_lstclear(&front, del);
			return (NULL);
		}
		ft_lstadd_back(&front, new);
		lst = lst->next;
	}
	return (front);
}
