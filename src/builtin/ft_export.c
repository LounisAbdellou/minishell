/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:14:17 by labdello          #+#    #+#             */
/*   Updated: 2024/09/16 17:52:54 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *str)
{
	size_t	i;

	i = 0;
	if (str[i] != '_' && !ft_isalpha(str[i]))
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] != '_' && !ft_isalnum(str[i]))
			return (0);
		i++;
	}
	return (1);
}

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

int	exec_export(char *arg, t_env *env)
{
	size_t	pos;
	char	**tab;

	tab = ft_split(arg, '=');
	if (!tab)
		return (0);
	if (!check_identifier(tab[0]))
	{
		ft_free_tab(tab);
		return (0);
	}
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
	return (ft_free_tab(tab), 1);
}

int	ft_export(char **args, t_env *env)
{
	size_t	i;

	i = 1;
	if (ft_tablen(args) < 2)
	{
		ft_env(env->vars);
		return (0);
	}
	while (args[i] != NULL)
	{
		if (!ft_strchr(args[i], '='))
			break ;
		if (!exec_export(args[i], env))
			return (1);
		i++;
	}
	return (0);
}
