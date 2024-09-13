/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:13:50 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/13 19:47:37 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(t_cmd **cmds)
{
	t_cmd	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->in && cmd->in > 1)
			close(cmd->in);
		if (cmd->out && cmd->out > 1)
			close(cmd->out);
		cmd = cmd->next;
	}
}

void	init_files(t_cmd **cmds, t_env *env)
{
	t_cmd	*current;
	t_file	*to_read;
	t_file	*to_write;

	current = *cmds;
	while (current)
	{
		to_read = current->to_read;
		to_write = current->to_write;
		if (to_read)
			current->in = set_file(to_read, env);
		if (to_write)
			current->out = set_file(to_write, env);
		current = current->next;
	}
}

void	init_pipes(t_cmd **cmds)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = *cmds;
	if (cmd->in == -2)
		cmd->in = 0;
	while (cmd)
	{
		if (pipe(fd) < 0)
			error_from_exec(cmds, 255);
		if (cmd->next == NULL && cmd->out == -2)
		{
			close(fd[1]);
			cmd->out = 1;
		}
		if (cmd->out == -2)
			cmd->out = fd[1];
		else
			close(fd[1]);
		if (cmd->next && cmd->next->in == -2)
			cmd->next->in = fd[0];
		else
			close(fd[0]);
		cmd = cmd->next;
	}
}

int	wait_for_all(t_cmd **cmds)
{
	t_cmd	*cmd;
	int		status;

	cmd = *cmds;
	status = 0;
	while (cmd)
	{
		if (cmd->pid > 0)
			waitpid(cmd->pid, &status, 0);
		if (cmd->pid < 0)
			break ;
		cmd = cmd->next;
	}
	if (WIFEXITED(status) && !g_signal_status)
		return (WEXITSTATUS(status));
	if ((WIFEXITED(status) && g_signal_status))
		return (128 + g_signal_status);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}

int	check_cmd(t_cmd *current)
{
	if (!current->path)
		return (2);
	if (access(current->path, F_OK) != 0)
		return (127);
	if (access(current->path, X_OK) != 0)
		return (126);
	if (current->in < 0 || current->out < 0)
		return (1);
	return (0);
}
