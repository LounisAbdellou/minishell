/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:17:23 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/17 18:07:56 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// static void	print_error(int status)
// {
// 	char	*err;
//
// 	// err = strerror(status);
// 	(void)status;
// 	err = strerror(128);
// 	printf("Minishell error : %s\n", err);
// 	return ;
// }

void	error_from_exec(t_cmd **cmds, int why)
{
	close_pipes(cmds);
	free_cmds(cmds);
	if (why == 2)
		exit(1);
	perror("Minishell error ");
	// print_error(why);
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
