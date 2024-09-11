/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:49:48 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 18:08:14 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **args)
{
	if (ft_tablen(args) > 2)
		return (1);
	if (ft_tablen(args) < 2)
	{
		if (chdir(getenv("HOME")) != 0)
			return (1);
		return (0);
	}
	if (chdir(args[1]) != 0)
		return (1);
	return (0);
}
