/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:45:33 by labdello          #+#    #+#             */
/*   Updated: 2024/09/16 18:54:20 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_nl_flag(char *arg)
{
	size_t	i;

	i = 2;
	if (ft_strncmp(arg, "-n", 2) != 0)
		return (0);
	while (arg[i] == 'n')
		i++;
	if (arg[i] != '\0')
		return (0);
	return (1);
}

int	ft_echo(char **args)
{
	size_t	i;
	int		nl;

	i = 1;
	nl = 1;
	if (!args[i])
	{
		ft_putstr_fd("\n", 1);
		return (0);
	}
	if (check_nl_flag(args[i]))
	{
		nl = 0;
		i++;
	}
	while (args[i] != NULL)
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1] != NULL)
			ft_putchar_fd(' ', 1);
		i++;
	}
	if (nl)
		ft_putchar_fd('\n', 1);
	return (0);
}
