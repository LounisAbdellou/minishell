/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nbrlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 08:47:08 by labdello          #+#    #+#             */
/*   Updated: 2024/05/15 09:01:54 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_nbrlen(int nbr)
{
	unsigned int	nb;
	size_t			count;

	nb = nbr;
	count = 1;
	if (nbr < 0)
	{
		nb = -nbr;
		count++;
	}
	while (nb / 10 >= 1)
	{
		nb = nb / 10;
		count++;
	}
	return (count);
}
