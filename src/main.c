/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/09/17 19:11:17 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal_status = 0;

static int	minishell_do(char *input, t_env *env)
{
	t_word		*token;
	t_operation	*ops;

	if (!should_parse(input))
		return (1);
	token = NULL;
	ops = NULL;
	if (!tokenize_input(input, &token, env))
		return (free_words(&token), 0);
	if (!analyze_syntax(&token))
	{
		env->last_status = 2;
		return (free_words(&token), 0);
	}
	if (!parse_tree(&token, &ops, env))
		return (free_parse(&token, &ops), 0);
	if (execute_tree(&ops, env) == -1)
		return (free_parse(&token, &ops), -1);
	return (free_parse(&token, &ops), 1);
}

void	minishell(char *station, t_env *env)
{
	char	*line;
	char	*prompt;

	while (1)
	{
		g_signal_status = 0;
		prompt = get_prompt(station);
		if (!prompt)
			line = readline("minishell$ ");
		else
		{
			line = readline(prompt);
			free(prompt);
		}
		if (!line || minishell_do(line, env) == -1)
		{
			if (line)
				free(line);
			break ;
		}
		add_history(line);
		free(line);
	}
	rl_clear_history();
}

int	main(int ac, char **av, char **env)
{
	t_env	local_env;
	char	*station;

	(void)ac;
	(void)av;
	if (!init_env(&local_env, env))
		return (free_env(&local_env), 1);
	sort_env(&local_env.virtual_vars);
	station = get_station(getenv("SESSION_MANAGER"));
	signal(SIGINT, &readline_sig);
	signal(SIGQUIT, SIG_IGN);
	minishell(station, &local_env);
	free_env(&local_env);
	if (station)
		free(station);
	return (0);
}
