/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_2dtab.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 18:01:50 by labdello          #+#    #+#             */
/*   Updated: 2024/08/13 18:16:15 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_print_2dtab(char ***tab)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (tab[i] != NULL)
	{
		j = 0;
		ft_printf("tab[%d] => {\n", i);
		while (tab[i][j] != NULL)
		{
			ft_printf("  tab[%d][%d] => %s\n", i, j, tab[i][j]);
			j++;
		}
		ft_printf("}\n");
		if (tab[i + 1] != NULL)
			ft_printf("\n");
		i++;
	}
}
