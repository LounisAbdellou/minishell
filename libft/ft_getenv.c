/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:14:18 by labdello          #+#    #+#             */
/*   Updated: 2024/09/10 15:22:55 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_getenv(char *var_name, char **env)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (env[i] != NULL)
	{
		j = 0;
		while (env[i][j] != '\0' && env[i][j] != '=')
			j++;
		str = ft_strndup(env[i], j);
		if (ft_strcmp(str, var_name) == 0)
		{
			free(str);
			return (env[i] + j + 1);
		}
		free(str);
		i++;
	}
	return (NULL);
}
