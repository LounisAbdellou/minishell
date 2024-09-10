/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 19:40:27 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/10 15:31:01 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_word	*skip_parenthesis(t_word *token)
{
	t_word	*current;
	int		open;
	int		close;

	current = token;
	close = 0;
	open = 0;
	while (current)
	{
		if (current->type == 8)
			open++;
		if (current->type == 9)
			close++;
		if (open && open == close)
			return (current);
		current = current->next;
	}
	return (NULL);
}

static t_cmd	*cmd_last_or_new(t_word *t, t_operation **ops)
{
	t_cmd		*cmd;
	t_cmd		*new;
	t_operation	*op;

	op = ft_oplast(*ops);
	cmd = op->cmd;
	new = NULL;
	if (t->type == 10)
	{
		new = ft_cmdnew(-1);
		if (!new)
			return (NULL);
		ft_cmdadd_back(new, &cmd);
		return (cmd);
	}
	cmd = ft_cmdlast(cmd);
	return (cmd);
}

static int	next_op(t_word *t, t_operation **ops)
{
	t_operation	*op;

	op = NULL;
	if (t->type == 6)
		op = ft_opnew(0);
	else
		op = ft_opnew(1);
	if (!op)
		return (0);
	ft_opadd_back(op, ops);
	return (1);
}

static int	recursive_parse(t_word *token, t_cmd **cmds, t_env *env)
{
	t_operation	*sub;
	t_cmd		*new;

	sub = NULL;
	if ((*cmds)->type == -1)
	{
		new = *cmds;
		new->type = 2;
	}
	else
		new = ft_cmdnew(2);
	if (!new)
		return (0);
	if (!parse_tree(&token, &sub, env))
		return (0);
	new->sub = sub;
	return (1);
}

int	generate_tree(t_word *t, t_operation **ops, t_env *env)
{
	t_cmd	*cmd;

	cmd = NULL;
	cmd = cmd_last_or_new(t, ops);
	if (!cmd)
		return (0);
	if (t->type == 1 && !set_path_cmd(t, cmd, env))
		return (0);
	else if (cmd && t->type == 2 && !set_arg_cmd(t, cmd))
		return (0);
	else if (t->type >= 11 && t->type <= 14 && !set_file_cmd(t, cmd))
		return (0);
	else if ((t->type == 6 || t->type == 7) && !next_op(t, ops))
		return (0);
	else if (t->type == 8)
		return (recursive_parse(t->next, &cmd, env));
	return (1);
}
