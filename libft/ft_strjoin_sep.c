/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_sep.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 15:46:58 by labdello          #+#    #+#             */
/*   Updated: 2024/08/22 15:51:42 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_sep(char *s1, char *s2, char *sep)
{
	size_t	total_len;
	char	*copy;

	if (!s1 || !s2 || !sep)
		return (NULL);
	total_len = ft_strlen(s1) + ft_strlen(s2) + ft_strlen(sep);
	copy = malloc(sizeof(char) * (total_len + 1));
	if (!copy)
		return (NULL);
	*copy = '\0';
	ft_strcat(copy, s1);
	ft_strcat(copy, sep);
	ft_strcat(copy, s2);
	return (copy);
}
