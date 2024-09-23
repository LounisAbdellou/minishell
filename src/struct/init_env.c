/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 18:22:21 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 18:08:09 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	set_vars(t_env *local_env, char **env, char **blvl, char **env_var)
{
	char	**tab;

	if (!env[0] && ft_tablen(env) < 1)
	{
		tab = ft_calloc(2, sizeof(char *));
		if (!tab)
			return (0);
		tab[0] = ft_strdup("SHLVL=1");
		local_env->vars = tab;
		return (1);
	}	
	*blvl = ft_itoa(ft_atoi(getenv("SHLVL")) + 1);
	*env_var = ft_strjoin("SHLVL=", *blvl);
	local_env->vars = ft_tabdup(env);
	if (!local_env->vars)
		local_env->vars = ft_calloc(1, sizeof(char *));
	if (!local_env->vars)
		return (0);
	local_env->virtual_vars = ft_tabdup(local_env->vars);
	if (!local_env->virtual_vars)
		return (0);
	return (1);
}

int	init_env(t_env *local_env, char **env)
{
	char	*env_path;
	char	*bash_lvl;
	char	*env_var;

	local_env->fd_in = dup(STDIN_FILENO);
	local_env->fd_out = dup(STDOUT_FILENO);
	local_env->last_status = 0;
	local_env->s_expand = 0;
	local_env->is_env = 0;
	local_env->s_exit = 0;
	local_env->is_err = 0;
	env_path = getenv("PATH");
	if (!env_path)
		env_path = ENV_PATH;
	local_env->path = ft_strdup(env_path);
	if (!set_vars(local_env, env, &bash_lvl, &env_var))
		return (0);
	exec_export(env_var, local_env);
	if (env_var)
		free(env_var);
	if (bash_lvl)
		free(bash_lvl);
	return (1);
}

void	free_env(t_env *local_env)
{
	if (local_env->path)
		free(local_env->path);
	if (local_env->vars)
		ft_free_tab(local_env->vars);
	if (local_env->virtual_vars)
		ft_free_tab(local_env->virtual_vars);
	close(local_env->fd_in);
	close(local_env->fd_out);
}
