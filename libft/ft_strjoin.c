/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/10 00:06:05 by labdello          #+#    #+#             */
/*   Updated: 2024/04/17 15:18:52 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_len;
	char	*copy;

	if (!s1 || !s2)
		return (NULL);
	total_len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	copy = (char *) malloc(sizeof(char) * (total_len + 1));
	if (!copy)
		return (NULL);
	*copy = '\0';
	ft_strcat(copy, (char *)s1);
	ft_strcat(copy, (char *)s2);
	return (copy);
}
