/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 14:30:46 by labdello          #+#    #+#             */
/*   Updated: 2024/09/12 14:13:58 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_tabdup(char **src_tab)
{
	size_t	i;
	char	**tab;

	if (!src_tab)
		return (NULL);
	i = 0;
	tab = ft_calloc(ft_tablen(src_tab) + 1, sizeof(char *));
	while (src_tab[i] != NULL)
	{
		tab[i] = ft_strdup(src_tab[i]);
		if (!tab[i])
		{
			ft_free_tab(tab);
			return (NULL);
		}
		i++;
	}
	return (tab);
}
