/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_lst.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/03 16:30:22 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 15:19:50 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_entry_list	*entry_lstnew(char *entry_name)
{
	t_entry_list	*node;

	node = malloc(sizeof(t_entry_list));
	if (!node)
		return (NULL);
	node->prev = NULL;
	node->next = NULL;
	node->name = ft_strdup(entry_name);
	return (node);
}

t_entry_list	*entry_lstlast(t_entry_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	entry_lstadd_front(t_entry_list **lst, t_entry_list *new)
{
	if (!lst || !new)
		return ;
	if (!(*lst))
	{
		*lst = new;
		return ;
	}
	new->next = *lst;
	(*lst)->prev = new;
	*lst = new;
}

size_t	entry_lstlen(t_entry_list *lst)
{
	size_t	len;

	len = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		len++;
	}
	return (len);
}

void	lst_to_tab(char ***args, t_entry_list *lst)
{
	size_t			i;
	char			**tab;
	t_entry_list	*tmp_node;

	i = 0;
	tab = malloc(sizeof(char *) * (entry_lstlen(lst) + 1));
	if (!tab)
		return ;
	while (lst != NULL)
	{
		tab[i] = lst->name;
		tmp_node = lst->next;
		free(lst);
		lst = tmp_node;
		i++;
	}
	tab[i] = NULL;
	ft_free_tab(*args);
	*args = tab;
}
