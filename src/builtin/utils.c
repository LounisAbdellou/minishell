/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:00 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 17:04:18 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_var_pos(char *var_name, char **env, size_t *pos)
{
	size_t	i;
	size_t	len;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i] != NULL)
	{
		if (ft_strncmp(env[i], var_name, len) == 0 && env[i][len] == '=')
		{
			*pos = i;
			return (1);
		}
		i++;
	}
	return (0);
}
