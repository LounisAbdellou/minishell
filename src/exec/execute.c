/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 18:06:43 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/20 18:53:10 by rbouselh         ###   ########.fr       */
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
		status = ft_unset(cmd->args, env);
	if (!ft_strcmp(cmd->path, "export"))
		status = ft_export(cmd->args, env);
	if (!ft_strcmp(cmd->path, "exit"))
		status = ft_exit(cmd->args, env);
	if (!ft_strcmp(cmd->path, "pwd"))
		status = ft_pwd();
	if (!ft_strcmp(cmd->path, "env"))
		status = ft_env(env->vars, 0);
	return (status);
}

static void	execute_this(t_cmd *cmd, t_cmd **cmds, t_env *env)
{
	int	status;

	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	handle_wildcard(&cmd->args);
	if (cmd->type == 0)
	{
		status = execblt(cmd, env);
		exit(status);
	}
	else if (cmd->type == 2)
	{
		status = execute_tree(&(cmd->sub), env);
		close(env->fd_in);
		close(env->fd_out);
		exit(status);
	}
	else
	{
		close(env->fd_in);
		close(env->fd_out);
		if (execve(cmd->path, cmd->args, env->vars) == -1)
			error_from_exec(cmds, 1, env);
	}
	return ;
}

static void	execute_cmd(t_cmd **cmds, t_cmd *current, t_env *env)
{
	current->pid = fork();
	if (current->pid == 0)
	{
		if (current->out > 1)
			dup2(current->out, STDOUT_FILENO);
		if (check_cmd(current))
			error_from_exec(cmds, check_cmd(current), env);
		else
		{
			if (current->in > 1)
				dup2(current->in, STDIN_FILENO);
			close_pipes(cmds);
			execute_this(current, cmds, env);
		}
	}
	else if (current->pid < 0)
		error_from_exec(cmds, 1, env);
}

static int	execute_op(t_cmd **cmds, t_cmd *current, t_env *env)
{
	int	status;

	init_files(cmds, env);
	init_pipes(cmds, env);
	config_cmd_sig(0);
	if (current->next == NULL && current->type == 0)
	{
		if (check_cmd(current))
			return (check_cmd(current));
		dup2(current->out, STDOUT_FILENO);
		if (current->in > -1)
			dup2(current->in, STDIN_FILENO);
		close_pipes(cmds);
		handle_wildcard(&current->args);
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
		env->s_exit = 0;
		env->is_err = 0;
		if (!should_exec(op))
			op->s_exec = op->prev->s_exec;
		else
		{
			op->s_exec = execute_op(&(op->cmd), op->cmd, env);
			env->last_status = op->s_exec;
			config_cmd_sig(1);
		}
		if (env->s_exit)
			return (printf("exit\n"), -1);
		status = op->s_exec;
		op = op->next;
	}
	return (status);
}
