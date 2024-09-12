/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:26:45 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/11 18:58:31 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_file	*ft_filenew(char *str, int type)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		return (NULL);
	new->name = str;
	new->fd = -2;
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_fileadd_back(t_file *new, t_file **lst)
{
	t_file	*current;

	current = *lst;
	if (!current)
	{
		*lst = new;
		return ;
	}
	while (current->next)
		current = current->next;
	current->next = new;
	new->prev = current;
	return ;
}

void	free_file(t_file **lst)
{
	t_file	*token;
	t_file	*tmp;

	token = *lst;
	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->name)
			free(tmp->name);
		free(tmp);
		tmp = NULL;
	}
	return ;
}
