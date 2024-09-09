/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 15:41:20 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 17:39:36 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_unset(char **args, char ***env)
{
	size_t	i;
	size_t	pos;

	i = 1;
	while (args[i] != NULL)
	{
		if (!find_var_pos(args[i], *env, &pos))
		{
			i++;
			continue ;
		}
		while ((*env)[pos] != NULL)
		{
			(*env)[pos] = (*env)[pos + 1];
			pos++;
		}
		i++;
	}
	return (0);
}
