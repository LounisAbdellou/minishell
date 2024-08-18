/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:12:48 by labdello          #+#    #+#             */
/*   Updated: 2024/08/05 16:13:04 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_hexlen(unsigned int hex)
{
	size_t			count;

	count = 1;
	while (hex / 16 >= 1)
	{
		hex = hex / 16;
		count++;
	}
	return (count);
}
