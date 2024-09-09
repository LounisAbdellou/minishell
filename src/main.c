/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 17:10:32 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minishell_do(char *input, char **env)
{
	t_word		*token;
	t_operation	*ops;

	if (!input[0])
		return (1);
	token = NULL;
	ops = NULL;
	if (!tokenize_input(input, &token))
		return (free_words(&token), 0);
	if (!analyze_syntax(&token))
		return (free_words(&token), 0);
	if (!parse_tree(&token, &ops))
		return (free_parse(&token, &ops), 0);
	execute_tree(&ops, env);
	return (free_parse(&token, &ops), 1);
}

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
		if (!line || minishell_do(line, env) == -1)
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
