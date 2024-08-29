/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:40:37 by labdello          #+#    #+#             */
/*   Updated: 2024/09/09 17:35:31 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **env)
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
	return (0);
}
