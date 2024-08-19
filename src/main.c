/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/09/02 15:59:13 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell(char *station, char **env)
{
	char	*line;
	char	*prompt;

	(void)env;
	while (1)
	{
		prompt = get_prompt(station);
		if (!prompt)
			line = readline("minishell$ ");
		else
		{
			line = readline(prompt);
			free(prompt);
		}
		if (!line)
			break ;
		add_history(line);
		free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	char	*station;

	(void)ac;
	(void)av;
	if (!env[0] && ft_tablen(env) < 1)
		return (1);
	station = get_station(getenv("SESSION_MANAGER"));
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(station, env);
	if (station)
		free(station);
	return (0);
}
