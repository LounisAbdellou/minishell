/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_dev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 12:20:14 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/04 15:46:49 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_lst_word(t_word *lst)
{
	t_word	*current;

	current = lst;
	if (!current)
		return ;
	while (current)
	{
		printf("content : '%s', type : %d\n", current->content, current->type);
		current = current->next;
	}
}

void	print_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		printf("tab[%d] : %s\n", i, tab[i]);
		i++;
	}
}

void	print_cmds(t_cmd **cmds)
{
	t_cmd	*cmd;
	int		i;

	cmd = *cmds;
	i = 0;
	while (cmd)
	{
		printf("cmd %d : %p, type : %d, next : %p\n", i, cmd, cmd->type, cmd->next);
		printf("path : %s, to_read : %d, to_write: %d, pid : %d\n", cmd->path, cmd->to_read, cmd->to_write, cmd->pid);
		if (cmd->type != 2 && cmd->type != -1)
			print_tab(cmd->args);
		else
			print_tree(&(cmd->sub), 1);
		cmd = cmd->next;
		i++;
	}
}

void	print_tree(t_operation **ops, int is_sub)
{
	t_operation *op;
	int			i;

	i = 0;
	op = *ops;
	if (is_sub)
		printf("\nSUB :\n");
	else
		printf("\nOP :\n");
	while (op)
	{
		printf("op %d : %p, type : %d\n", i, op, op->type);
		if (op->cmd)
			print_cmds(&(op->cmd));
		else
			printf("pas de cmds...\n");
		op = op->next;
		i++;
	}
}
