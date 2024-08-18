/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 20:05:51 by labdello          #+#    #+#             */
/*   Updated: 2024/05/25 11:56:59 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_charset(char c, const char *charset)
{
	size_t	i;

	i = 0;
	while (charset[i] != '\0')
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start_i;
	size_t	str_size;

	i = 0;
	if (!s1)
		return (NULL);
	while (is_charset(s1[i], set))
		i++;
	start_i = i;
	i = ft_strlen((char *)s1) - 1;
	while (is_charset(s1[i], set) && start_i < i)
		i--;
	str_size = (i - start_i) + 1;
	if (start_i > i)
		return (ft_strnew(0));
	return (ft_strndup(s1 + start_i, str_size));
}
