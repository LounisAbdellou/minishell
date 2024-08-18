/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 16:11:52 by labdello          #+#    #+#             */
/*   Updated: 2024/08/05 16:18:23 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_ptrlen(unsigned long long ptr)
{
	size_t			count;

	count = 1;
	while (ptr / 16 >= 1)
	{
		ptr = ptr / 16;
		count++;
	}
	return (count);
}

void	ft_putptr(unsigned long long ptr, int fd)
{
	if (ptr >= 16)
	{
		ft_putptr(ptr / 16, fd);
		ft_putptr(ptr % 16, fd);
	}
	else
	{
		if (ptr <= 9)
			ft_putchar_fd(ptr + 48, fd);
		else
			ft_putchar_fd((ptr - 10) + 97, fd);
	}
}

size_t	ft_unbrlen(unsigned int nbr)
{
	size_t			count;

	count = 1;
	while (nbr / 10 >= 1)
	{
		nbr = nbr / 10;
		count++;
	}
	return (count);
}

void	ft_putunbr_fd(unsigned int nbr, int fd)
{
	if (nbr >= 10)
	{
		ft_putnbr_fd(nbr / 10, fd);
		ft_putnbr_fd(nbr % 10, fd);
	}
	else
		ft_putchar_fd(nbr + 48, fd);
}
