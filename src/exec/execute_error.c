/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:23 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/13 19:48:23 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	return_error(void)
{
	static int	has_err;

	if (!has_err)
		perror("Minishell error");
	has_err = 1;
}

void	error_from_exec(t_cmd **cmds, int why)
{
	close_pipes(cmds);
	free_cmds(cmds);
	if (why == 2)
		exit(0);
	return_error();
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
