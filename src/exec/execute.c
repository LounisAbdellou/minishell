/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:06:43 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/12 14:09:33 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	return_error(void)
{
	static int	has_err;

	if (!has_err)
		perror("Pipex error");
	has_err = 1;
}

void	error_from_exec(t_cmd **cmds)
{
	close_pipes(cmds);
	free_cmds(cmds);
	return_error();
	exit(1);
}

static int	execblt(t_cmd *cmd, t_env *env)
{
	int	status;

	status = 0;
	if (!ft_strcmp(cmd->path, "echo"))
		status = ft_echo(cmd->args);
	if (!ft_strcmp(cmd->path, "cd"))
		status = ft_cd(cmd->args);
	if (!ft_strcmp(cmd->path, "unset"))
		status = ft_unset(cmd->args, &env->vars);
	if (!ft_strcmp(cmd->path, "export"))
		status = ft_export(cmd->args, &env->vars);
	if (!ft_strcmp(cmd->path, "exit"))
		status = 0;
	if (!ft_strcmp(cmd->path, "pwd"))
		status = ft_pwd();
	if (!ft_strcmp(cmd->path, "env"))
		status = ft_env(env->vars);
	return (status);
}

void	execute_this(t_cmd *cmd, t_cmd **cmds, t_env *env)
{
	int	status;

	if (cmd->type == 0)
	{
		status = execblt(cmd, env);
		exit(status);
	}
	else if (cmd->type == 2)
	{
		status = execute_tree(&(cmd->sub), env);
		exit(status);
	}
	else
	{
		if (execve(cmd->path, cmd->args, env->vars) == -1)
			error_from_exec(cmds);
	}
	return ;
}

int	execute_tree(t_operation **ops, t_env *env)
{
	t_operation	*op;
	int			res;

	op = *ops;
	while (op)
	{
		if (op->type == 2)
			execute_cmd(op, &(op->cmd), op->cmd, env);
		else if (op->prev && op->type == op->prev->s_exec)
			execute_cmd(op, &(op->cmd), op->cmd, env);
		else if (op->prev && op->type == 1 && op->prev->s_exec != 0)
			execute_cmd(op, &(op->cmd), op->cmd, env);
		if (op->prev && op->s_exec == -1)
			op->s_exec = op->prev->s_exec;
		res = op->s_exec;
		op = op->next;
	}
	return (res);
}
