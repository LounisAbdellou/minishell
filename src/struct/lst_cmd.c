/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 16:59:50 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/04 15:50:17 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*ft_cmdnew(int type)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->type = type;
	new->pid = 0;
	new->next = NULL;
	new->prev = NULL;
	new->path = NULL;
	new->args = NULL;
	new->sub = NULL;
	new->to_read = -2;
	new->to_write = -2;
	return (new);
}

void	ft_cmdadd_back(t_cmd *new, t_cmd **lst)
{
	t_cmd	*current;

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

t_cmd	*ft_cmdlast(t_cmd *cmd)
{
	t_cmd	*current;

	if (!cmd)
		return (NULL);
	current = cmd;
	while (current && current->next)
		current = current->next;
	return (current);
}

void	free_cmds(t_cmd **lst)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = *lst;
	while (cmd)
	{
		tmp = cmd;
		if (cmd->path)
			free(cmd->path);
		if (cmd->args)
			ft_free_tab(cmd->args);
		if (cmd->sub)
			free_operations(&(cmd->sub));
		cmd = cmd->next;
		free(tmp);
		tmp = NULL;
	}
}
