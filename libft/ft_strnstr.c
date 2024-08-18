/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 14:42:42 by labdello          #+#    #+#             */
/*   Updated: 2024/04/21 02:16:49 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *str, char *needle, size_t n)
{
	size_t	i;
	size_t	j;

	i = 0;
	if (ft_strlen(needle) < 1)
		return (str);
	while (i < n && str[i] != '\0')
	{
		j = 0;
		while (i + j < n && needle[j] != '\0' && str[i + j] == needle[j])
			j++;
		if (j == ft_strlen(needle))
			return (str + i);
		i++;
	}
	return (NULL);
}
