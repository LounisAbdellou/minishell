/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 22:54:45 by labdello          #+#    #+#             */
/*   Updated: 2024/05/22 15:47:24 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char const *s, size_t n)
{
	size_t	i;
	char	*copy;

	i = 0;
	copy = (char *) malloc(sizeof(char) * (n + 1));
	if (!copy)
		return (NULL);
	copy[0] = '\0';
	while (i < n && s[i] != '\0')
	{
		copy[i] = s[i];
		i++;
	}
	copy[i] = '\0';
	return (copy);
}
