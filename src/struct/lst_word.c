/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_word.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 16:26:45 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/02 12:17:22 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_word	*ft_wordnew(char *str)
{
	t_word	*new;

	new = malloc(sizeof(t_word));
	if (!new)
		return (NULL);
	new->content = str;
	new->type = 0;
	new->next = NULL;
	new->prev = NULL;
	return (new);
}

void	ft_wordadd_back(t_word *new, t_word **lst)
{
	t_word	*current;

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

void	free_words(t_word **lst)
{
	t_word	*token;
	t_word	*tmp;

	token = *lst;
	while (token)
	{
		tmp = token;
		token = token->next;
		if (tmp->content)
			free(tmp->content);
		free(tmp);
		tmp = NULL;
	}
	return ;
}
