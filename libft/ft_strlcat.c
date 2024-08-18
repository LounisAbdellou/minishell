/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 23:32:13 by labdello          #+#    #+#             */
/*   Updated: 2024/06/04 12:24:19 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, char *src, size_t n)
{
	size_t	i;
	size_t	src_len;
	size_t	dest_len;

	i = 0;
	if (!n)
		return (ft_strlen(src));
	src_len = ft_strlen(src);
	dest_len = ft_strlen(dest);
	if (n <= dest_len)
		return (src_len + n);
	while ((dest_len + i) < (n - 1) && src[i] != '\0')
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}
