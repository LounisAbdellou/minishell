/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/06 15:29:00 by labdello          #+#    #+#             */
/*   Updated: 2024/09/19 19:28:20 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_identifier(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
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

int	find_var_pos(char *var_name, char **env, size_t *pos)
{
	size_t	i;
	size_t	len;
	int		is_cmp;

	i = 0;
	len = ft_strlen(var_name);
	while (env[i] != NULL)
	{
		is_cmp = ft_strncmp(env[i], var_name, len) == 0;
		if (is_cmp && (env[i][len] == '=' || env[i][len] == '\0'))
		{
			*pos = i;
			return (1);
		}
		i++;
	}
	return (0);
}
