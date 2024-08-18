/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 14:18:28 by labdello          #+#    #+#             */
/*   Updated: 2024/08/05 16:21:07 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unbrlen(unsigned int nbr);
size_t	ft_ptrlen(unsigned long long ptr);
void	ft_putunbr_fd(unsigned int nbr, int fd);
void	ft_putptr(unsigned long long ptr, int fd);

int	ft_handle_str(char *str)
{
	size_t	len;

	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	len = ft_strlen(str);
	ft_putstr_fd(str, 1);
	return (len);
}

int	ft_handle_digit(int nbr)
{
	size_t	len;

	len = ft_nbrlen(nbr);
	ft_putnbr_fd(nbr, 1);
	return (len);
}

int	ft_handle_unsigned(unsigned int nbr)
{
	size_t	len;

	len = ft_unbrlen(nbr);
	ft_putunbr_fd(nbr, 1);
	return (len);
}

int	ft_handle_hex(unsigned int hex, char convertion)
{
	size_t	len;

	len = ft_hexlen(hex);
	if (convertion == 'p')
	{
		ft_putstr_fd("0x", 1);
		len += 2;
	}
	ft_puthex_fd(hex, ft_isupper(convertion), 1);
	return (len);
}

int	ft_handle_ptr(unsigned long long ptr)
{
	size_t	len;

	if (ptr == 0)
	{
		ft_putstr_fd("(nil)", 1);
		return (5);
	}
	len = ft_ptrlen(ptr);
	ft_putstr_fd("0x", 1);
	ft_putptr(ptr, 1);
	return (len + 2);
}
