/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 19:26:26 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 15:19:54 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	entry_lstclear(t_entry_list **lst)
{
	t_entry_list	*tmp;

	if (!lst)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		free(*lst);
		*lst = tmp;
	}
}

void	expand_lst(t_entry_list **entry_lst, t_entry_list **new_entry_lst)
{
	t_entry_list	*new_last;
	t_entry_list	*prev;
	t_entry_list	*next;

	prev = (*entry_lst)->prev;
	next = (*entry_lst)->next;
	new_last = entry_lstlast(*new_entry_lst);
	(*new_entry_lst)->prev = prev;
	prev->next = *new_entry_lst;
	if (next != NULL)
	{
		next->prev = new_last;
		new_last->next = next;
	}
	free((*entry_lst)->name);
	free(*entry_lst);
	*entry_lst = new_last;
}

t_entry_list	*get_entries(void)
{
	DIR					*dir;
	t_entry_list		*lst;
	t_entry_list		*new;
	struct dirent		*dir_entry;

	lst = NULL;
	dir = opendir(".");
	dir_entry = readdir(dir);
	while (dir_entry != NULL)
	{
		dir_entry = readdir(dir);
		if (!dir_entry || dir_entry->d_name[0] == '.')
			continue ;
		new = entry_lstnew(dir_entry->d_name);
		if (!new)
			return (entry_lstclear(&lst), NULL);
		entry_lstadd_front(&lst, new);
	}
	closedir(dir);
	return (lst);
}

int	entry_lstmap(t_entry_list **entry_lst)
{
	t_entry_list	*start;
	t_entry_list	*new_entry_lst;

	start = *entry_lst;
	while (*entry_lst != NULL)
	{
		if (ft_ischr((*entry_lst)->name, '*'))
		{
			new_entry_lst = get_entries();
			if (!new_entry_lst)
				return (entry_lstclear(entry_lst), 0);
			expand_lst(entry_lst, &new_entry_lst);
		}
		*entry_lst = (*entry_lst)->next;
	}
	*entry_lst = start;
	return (1);
}

int	handle_wildcard(char ***args)
{
	int				i;
	t_entry_list	*new;
	t_entry_list	*entry_lst;

	if (!args || ft_tablen(*args) < 2)
		return (0);
	i = ft_tablen(*args) - 1;
	entry_lst = NULL;
	while (i >= 0)
	{
		new = entry_lstnew((*args)[i]);
		if (!new)
			return (entry_lstclear(&entry_lst), 0);
		entry_lstadd_front(&entry_lst, new);
		i--;
	}
	entry_lstmap(&entry_lst);
	if (entry_lst != NULL)
		lst_to_tab(args, entry_lst);
	return (1);
}
