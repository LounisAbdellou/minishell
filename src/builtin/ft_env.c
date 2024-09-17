/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:40:37 by labdello          #+#    #+#             */
/*   Updated: 2024/09/17 19:31:55 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sort_env(char ***env)
{
	size_t	i;
	char	*tmp;

	if (!(*env))
		return ;
	i = 0;
	while ((*env)[i] != NULL)
	{
		if ((*env)[i + 1] != NULL && ft_strcmp((*env)[i + 1], (*env)[i]) < 0)
		{
			tmp = (*env)[i];
			(*env)[i] = (*env)[i + 1];
			(*env)[i + 1] = tmp;
			i = 0;
		}
		else
			i++;
	}
}

void	print_export(char *var)
{
	size_t	i;
	int		is_first;

	i = 0;
	is_first = 1;
	ft_putstr_fd("declare -x ", 1);
	while (var[i] != '\0')
	{
		ft_putchar_fd(var[i], 1);
		if (var[i] == '=' && is_first)
		{
			is_first = 0;
			ft_putchar_fd('\"', 1);
		}
		if (var[i + 1] == '\0' && !is_first)
			ft_putchar_fd('\"', 1);
		i++;
	}
	ft_putchar_fd('\n', 1);
}

int	ft_env(char **env, int from_export)
{
	size_t	i;

	i = 0;
	while (env[i] != NULL)
	{
		if (from_export)
			print_export(env[i]);
		else
			ft_putendl_fd(env[i], 1);
		i++;
	}
	return (0);
}
