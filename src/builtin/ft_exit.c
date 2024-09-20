/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 14:10:27 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/19 19:31:28 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	get_exit_status(char *arg, int is_pos)
{
	long long	input;
	int			result;

	input = ft_atoll(arg);
	result = input % 256;
	if (is_pos)
		return (result);
	return (256 - result);
}

static int	check_exit(char **args, char *arg, t_env *env)
{
	int	i;
	int	len;

	i = 0;
	while (arg[i] && !ft_isspace(arg[i]))
	{
		if (!ft_isdigit(arg[i]))
			return (ft_putstr_fd("Numeric argument required\n", 2), 2);
			// return (printf("Numeric argument required\n"), 2);
		i++;
	}
	len = i;
	while (arg[i])
	{
		if (!ft_isspace(arg[i]))
			return (ft_putstr_fd("Numeric argument required\n", 2), 2);
			// return (printf("Numeric argument required\n"), 2);
		i++;
	}
	if (len > 19)
		return (ft_putstr_fd("Numeric argument required\n", 2), 2);
		// return (printf("Numeric argument required\n"), 2);
	if (ft_tablen(args) > 2)
	{
		env->s_exit = 0;
		return (ft_putstr_fd("Too many arguments\n", 2), 1);
		// return (printf("Too many arguments\n"), 1);
	}
	return (0);
}

int	ft_exit(char **args, t_env *env)
{
	int	i;
	int	is_pos;
	int	check;

	i = 0;
	env->s_exit = 1;
	is_pos = 1;
	if (!args[1])
		return (0);
	while (ft_isspace(args[1][i]))
		i++;
	if (args[1][i] == '+' || args[1][i] == '-')
	{
		if (args[1][i] == '-')
			is_pos = 0;
		i++;
	}
	while (args[1][i] && args[1][i] == '0')
		i++;
	check = check_exit(args, args[1] + i, env);
	if (check)
		return (check);
	return (get_exit_status(args[1] + i, is_pos));
}
