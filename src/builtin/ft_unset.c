/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:41:20 by labdello          #+#    #+#             */
/*   Updated: 2024/09/16 18:01:10 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_occ_count(char **args, t_env *env)
{
	size_t	n;
	size_t	i;
	size_t	count;

	i = 1;
	count = 0;
	while (args[i] != NULL)
	{
		if (find_var_pos(args[i], env->vars, &n))
			count++;
		i++;
	}
	return (count);
}

int	is_unset(char **args, char *var)
{
	size_t	i;
	size_t	len;

	i = 0;
	while (args[i] != NULL)
	{
		len = ft_strlen(args[i]);
		if (ft_strncmp(var, args[i], len) == 0 && var[len] == '=')
			return (1);
		i++;
	}
	return (0);
}

int	should_unset_path(char **args)
{
	size_t	i;

	i = 0;
	while (args[i] != NULL)
	{
		if (ft_strcmp(args[i], "PATH") == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exec_unset(char **args, t_env *env, char **tmp)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (tmp[i] != NULL)
	{
		if (!is_unset(args, tmp[i]))
		{
			env->vars[j] = tmp[i];
			j++;
		}
		else
			free(tmp[i]);
		i++;
	}
}

int	ft_unset(char **args, t_env *env)
{
	char	**tmp;
	size_t	occ_count;

	if (should_unset_path(args) && env->path != NULL)
	{
		free(env->path);
		env->path = NULL;
	}
	occ_count = get_occ_count(args, env);
	if (occ_count < 1)
		return (0);
	tmp = env->vars;
	env->vars = ft_calloc((ft_tablen(tmp) - occ_count) + 1, sizeof(char *));
	if (!env->vars)
	{
		env->vars = tmp;
		return (1);
	}
	exec_unset(args, env, tmp);
	free(tmp);
	return (0);
}
