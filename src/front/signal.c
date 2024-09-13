/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:30:34 by labdello          #+#    #+#             */
/*   Updated: 2024/09/13 18:46:45 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	readline_sig(int status)
{
	if (status == 2)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	cmd_sig(int status)
{
	if (status == 2)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
	}
	if (status == 3)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("Quit (core dumped)\n", 1);
		rl_on_new_line();
	}
}

void	heredoc_sig(int status)
{
	if (status == 2)
	{
		rl_replace_line("", 0);
		ft_putstr_fd("\n", 1);
		rl_on_new_line();
		unlink("/tmp/.heredoc");
		exit(status);
	}
}

void	config_cmd_sig(int is_reset)
{
	if (is_reset)
	{
		signal(SIGINT, &readline_sig);
		signal(SIGQUIT, SIG_IGN);
		return ;
	}
	signal(SIGINT, &cmd_sig);
	signal(SIGQUIT, &cmd_sig);
}
