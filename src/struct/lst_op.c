/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_op.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:59:32 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/02 12:23:03 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_operation	*ft_opnew(int type)
{
	t_operation	*new;
	t_cmd		*cmd;

	new = malloc(sizeof(t_operation));
	if (!new)
		return (NULL);
	new->type = type;
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	cmd = NULL;
	cmd = ft_cmdnew(-1);
	if (!cmd)
		return (free(new), NULL);
	new->cmd = cmd;
	return (new);
}

void	ft_opadd_back(t_operation *new, t_operation **lst)
{
	t_operation	*current;

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

t_operation	*ft_oplast(t_operation *op)
{
	t_operation	*current;

	if (!op)
		return (NULL);
	current = op;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	free_operations(t_operation **lst)
{
	t_operation	*op;
	t_operation	*tmp;

	op = *lst;
	while (op)
	{
		tmp = op;
		if (op->cmd)
			free_cmds(&(op->cmd));
		op = op->next;
		free(tmp);
		tmp = NULL;
	}
	return ;
}
