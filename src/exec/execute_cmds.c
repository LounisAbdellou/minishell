/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:13:50 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/09 14:52:33 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	close_pipes(t_cmd **cmds)
{
	t_cmd	*cmd;

	cmd = *cmds;
	while (cmd)
	{
		if (cmd->to_read && cmd->to_read > 1)
			close(cmd->to_read);
		if (cmd->to_write && cmd->to_write > 1)
			close(cmd->to_write);
		cmd = cmd->next;
	}
}

static void	init_pipes(t_cmd **cmds)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = *cmds;
	if (cmd->to_read == -2)
		cmd->to_read = 0;
	while (cmd)
	{
		if (pipe(fd) < 0)
			error_from_exec(cmds);
		if (cmd->next == NULL && cmd->to_write == -2)
		{
			close(fd[1]);
			cmd->to_write = 1;
		}
		if (cmd->to_write == -2)
			cmd->to_write = fd[1];
		else
			close(fd[1]);
		if (cmd->next && cmd->next->to_read == -2)
			cmd->next->to_read = fd[0];
		else
			close(fd[0]);
		cmd = cmd->next;
	}
}

void	wait_for_all(t_operation *op, t_cmd **cmds)
{
	t_cmd	*cmd;
	int		status;

	cmd = *cmds;
	while (cmd)
	{
		waitpid(cmd->pid, &status, 0);
		if (cmd->pid < 0)
			break ;
		op->s_exec = status;
		cmd = cmd->next;
	}
}

static int	check_cmd(t_cmd *current)
{
	if (current->to_read < 0)
		return (0);
	if (current->to_write < 0)
		return (0);
	return (1);
}

void	execute_cmd(t_operation *op, t_cmd **cmds, t_cmd *current, char **env)
{
	init_pipes(cmds);
	while (current)
	{
		current->pid = fork();
		if (current->pid == 0)
		{
			dup2(current->to_write, 1);
			if (!check_cmd(current))
				error_from_exec(cmds);
			else
			{
				if (current->to_read > -1)
					dup2(current->to_read, 0);
				close_pipes(cmds);
				execute_this(current, cmds, env);
			}
		}
		else if (current->pid < 0)
			error_from_exec(cmds);
		current = current->next;
	}
	close_pipes(cmds);
	wait_for_all(op, cmds);
}
