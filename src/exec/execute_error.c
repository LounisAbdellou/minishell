/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:23 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/23 13:13:44 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	print_blt_err(char *blt, char *arg, char *msg, int is_blt)
{
	if (is_blt)
		ft_putstr_fd("minishell: ", 2);
	else
		ft_putstr_fd("Minishell error: ", 2);
	if (blt)
	{
		ft_putstr_fd(blt, 2);
		ft_putstr_fd(": ", 2);
	}
	if (arg)
	{
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": ", 2);
	}
	if (msg)
		ft_putstr_fd(msg, 2);
	ft_putchar_fd('\n', 2);
}

static void	print_error(int *status, t_env *env)
{
	env->is_err++;
	if (*status == 129)
	{
		*status = 126;
		print_blt_err(NULL, NULL, "Is a directory", 0);
	}
	else if (*status == 126)
		print_blt_err(NULL, NULL, "permission denied", 0);
	else if (*status == 127)
		print_blt_err(NULL, NULL, "command not found", 0);
	return ;
}

void	error_from_exec(t_cmd **cmds, int why, t_env *env)
{
	close_pipes(cmds);
	free_cmds(cmds);
	if (why == 2)
		exit(1);
	if (why == 3)
		exit(0);
	if (env->is_err == 0)
		print_error(&why, env);
	exit(why);
}

int	should_exec(t_operation *op)
{
	if (op->type == 2)
		return (1);
	if (op->prev && op->type == 0 && op->prev->s_exec == 0)
		return (1);
	if (op->prev && op->type == 1 && op->prev->s_exec != 0)
		return (1);
	return (0);
}

int	check_is_cmd(t_cmd *current)
{
	struct stat	bf;
	int			check;

	check = ft_strncmp(current->path, "./", 2) != 0;
	if (access(current->path, F_OK) != 0)
		return (127);
	if (check && access(current->path, X_OK) != 0)
		return (127);
	if (access(current->path, X_OK) != 0)
		return (126);
	stat(current->path, &bf);
	if ((bf.st_mode & S_IFMT) == S_IFDIR)
	{
		if (ft_strncmp(current->path, "/", 1) == 0)
			return (129);
		if (ft_strncmp(current->path, "./", 2) != 0)
			return (127);
		return (129);
	}
	return (0);
}
