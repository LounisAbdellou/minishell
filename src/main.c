/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/09/12 14:18:46 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	minishell_do(char *input, t_env *env)
{
	t_word		*token;
	t_operation	*ops;

	if (!input || !input[0])
		return (1);
	token = NULL;
	ops = NULL;
	if (!tokenize_input(input, &token))
		return (free_words(&token), 0);
	if (!analyze_syntax(&token))
		return (free_words(&token), 0);
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

void	init_env(t_env *local_env, char **env)
{
	char	**tab;

	local_env->vars = ft_tabdup(env);
	local_env->fd_in = dup(0);
	local_env->fd_out = dup(1);
	local_env->path = getenv("PATH");
	if (!env[0] && ft_tablen(env) < 1)
	{
		local_env->path = ENV_PATH;
		tab = ft_calloc(2, sizeof(char *));
		if (!tab)
			return ;
		tab[0] = ft_strdup("_=/usr/bin/env");
		local_env->vars = tab;
	}
}

int	main(int ac, char **av, char **env)
{
	t_env	local_env;
	char	*station;

	(void)ac;
	(void)av;
	init_env(&local_env, env);
	station = get_station(getenv("SESSION_MANAGER"));
	signal(SIGINT, &signal_handler);
	signal(SIGQUIT, SIG_IGN);
	minishell(station, &local_env);
	if (local_env.vars)
		ft_free_tab(local_env.vars);
	close(local_env.fd_in);
	close(local_env.fd_out);
	if (station)
		free(station);
	return (0);
}
