/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:14:17 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 17:14:20 by rbouselh         ###   ########.fr       */
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

void	print_env(char **env)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_tablen(env);
	while (i < len)
	{
		ft_putendl_fd(env[i], 1);
		i++;
	}
}

void	append_var(char *arg, char ***env)
{
	size_t	len;

	len = ft_tablen(*env);
	(*env)[len] = arg;
	(*env)[len + 1] = NULL;
}

int	exec_export(char *arg, char ***env)
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
	if (!find_var_pos(tab[0], *env, &pos))
		append_var(arg, env);
	else
		(*env)[pos] = arg;
	ft_free_tab(tab);
	return (1);
}

int	ft_export(char **args, char ***env)
{
	size_t	i;

	i = 1;
	if (ft_tablen(args) < 2)
	{
		print_env(*env);
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
	print_env(*env);
	return (0);
}
