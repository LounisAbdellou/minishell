/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/02 19:11:42 by labdello          #+#    #+#             */
/*   Updated: 2024/08/05 16:14:23 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_puthex_fd(unsigned int hex, int capitilize, int fd)
{
	if (hex >= 16)
	{
		ft_puthex_fd(hex / 16, capitilize, fd);
		ft_puthex_fd(hex % 16, capitilize, fd);
	}
	else
	{
		if (hex <= 9)
			ft_putchar_fd(hex + 48, fd);
		else
		{
			if (capitilize)
				ft_putchar_fd((hex - 10) + 65, fd);
			else
				ft_putchar_fd((hex - 10) + 97, fd);
		}
	}
}
