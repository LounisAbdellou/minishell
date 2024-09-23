/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:49:48 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 17:09:30 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	if (ft_tablen(args) > 2)
	{
		print_blt_err("cd", NULL, "too many arguments", 1);
		return (1);
	}
	if (ft_tablen(args) < 2)
	{
		if (chdir(getenv("HOME")) != 0)
		{
			print_blt_err("cd", NULL, "HOME not set", 1);
			return (1);
		}
		return (0);
	}
	if (chdir(args[1]) != 0)
	{
		print_blt_err("cd", args[1], "No such file or directory", 1);
		return (1);
	}
	return (0);
}
