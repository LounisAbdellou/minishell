/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 17:34:42 by labdello          #+#    #+#             */
/*   Updated: 2024/05/21 17:58:35 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*src_ptr;
	unsigned char	*dest_ptr;

	if (!dest && !src)
		return (NULL);
	i = 0;
	src_ptr = (unsigned char *)src;
	dest_ptr = (unsigned char *)dest;
	if (dest_ptr > src_ptr)
		while (n--)
			dest_ptr[n] = src_ptr[n];
	else
	{
		while (i < n)
		{
			dest_ptr[i] = src_ptr[i];
			i++;
		}
	}
	return (dest);
}
