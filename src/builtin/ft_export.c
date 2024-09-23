/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:14:17 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 17:09:52 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	append_var(char *arg, char ***env)
{
	size_t		i;
	size_t		len;
	char		**tmp;

	i = -1;
	len = ft_tablen(*env);
	tmp = *env;
	*env = ft_calloc(len + 2, sizeof(char *));
	if (!(*env))
	{
		*env = tmp;
		return ;
	}
	while (++i < len)
	{
		(*env)[i] = ft_strdup(tmp[i]);
		if (!(*env)[i])
		{
			ft_free_tab(*env);
			*env = tmp;
			return ;
		}
	}
	(*env)[i] = ft_strdup(arg);
	ft_free_tab(tmp);
}

void	handle_env(char *arg, char **tab, t_env *env)
{
	size_t	pos;

	if (!ft_strchr(arg, '='))
		return ;
	if (ft_strcmp(tab[0], "PATH") == 0)
	{
		if (env->path)
			free(env->path);
		env->path = ft_strdup(ft_strchr(arg, '=') + 1);
	}
	if (!find_var_pos(tab[0], env->vars, &pos))
		append_var(arg, &(env->vars));
	else
	{
		free(env->vars[pos]);
		env->vars[pos] = ft_strdup(arg);
	}
}

void	handle_virtual_env(char *arg, char **tab, t_env *env)
{
	size_t	pos;

	if (!find_var_pos(tab[0], env->virtual_vars, &pos))
		append_var(arg, &(env->virtual_vars));
	else
	{
		free(env->virtual_vars[pos]);
		env->virtual_vars[pos] = ft_strdup(arg);
	}
}

int	exec_export(char *arg, t_env *env)
{
	char	**tab;

	tab = ft_split(arg, '=');
	if (!tab)
		return (0);
	if (!check_identifier(tab[0]))
	{
		ft_free_tab(tab);
		return (0);
	}
	handle_env(arg, tab, env);
	handle_virtual_env(arg, tab, env);
	return (ft_free_tab(tab), 1);
}

int	ft_export(char **args, t_env *env)
{
	size_t	i;

	i = 1;
	if (ft_tablen(args) < 2)
	{
		ft_env(env->virtual_vars, 1);
		return (0);
	}
	while (args[i] != NULL)
	{
		if (!exec_export(args[i], env))
		{
			print_blt_err("export", args[i], "not a valid identifier", 1);
			return (1);
		}
		i++;
	}
	return (0);
}
