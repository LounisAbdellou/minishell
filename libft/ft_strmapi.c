/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 17:37:55 by labdello          #+#    #+#             */
/*   Updated: 2024/04/17 15:18:06 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	i;
	char			*mapped_str;

	i = 0;
	if (!s || !f)
		return (NULL);
	mapped_str = (char *) malloc(sizeof(char) * (ft_strlen((char *)s) + 1));
	if (!mapped_str)
		return (NULL);
	mapped_str[ft_strlen((char *)s)] = '\0';
	while (s[i] != '\0')
	{
		mapped_str[i] = (*f)(i, s[i]);
		i++;
	}
	return (mapped_str);
}
