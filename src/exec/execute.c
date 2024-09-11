/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:06:43 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/12 15:05:27 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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

static void	execute_this(t_cmd *cmd, t_cmd **cmds, t_env *env)
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
		if (status == -2)
			exit(0);
		exit(status);
	}
	else
	{
		if (execve(cmd->path, cmd->args, env->vars) == -1)
			error_from_exec(cmds);
	}
	return ;
}

static void	execute_cmd(t_cmd **cmds, t_cmd *current, t_env *env)
{
	current->pid = fork();
	if (current->pid == 0)
	{
		close(env->fd_in);
		close(env->fd_out);
		dup2(current->out, 1);
		if (!check_cmd(current))
			error_from_exec(cmds);
		else
		{
			if (current->in > -1)
				dup2(current->in, 0);
			close_pipes(cmds);
			execute_this(current, cmds, env);
		}
	}
	else if (current->pid < 0)
		error_from_exec(cmds);
}

static int	execute_op(t_cmd **cmds, t_cmd *current, t_env *env)
{
	int	status;

	init_files(cmds);
	init_pipes(cmds);
	if (current->next == NULL && current->type == 0)
	{
		dup2(current->out, 1);
		if (current->in > -1)
			dup2(current->in, 0);
		close_pipes(cmds);
		status = execblt(current, env);
		return (dup2(env->fd_in, 0), dup2(env->fd_out, 1), status);
	}
	while (current)
	{
		execute_cmd(cmds, current, env);
		current = current->next;
	}
	close_pipes(cmds);
	return (wait_for_all(cmds));
}

int	execute_tree(t_operation **ops, t_env *env)
{
	t_operation	*op;
	int			status;

	op = *ops;
	status = -1;
	while (op)
	{
		if (!should_exec(op))
			op->s_exec = op->prev->s_exec;
		else
			op->s_exec = execute_op(&(op->cmd), op->cmd, env);
		if (op->s_exec == -2)
			return (printf("exit =)\n"), -1);
		status = op->s_exec;
		op = op->next;
	}
	return (status);
}
