/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 14:53:13 by labdello          #+#    #+#             */
/*   Updated: 2024/06/20 12:50:19 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	max_len;

	if (!s)
		return (NULL);
	else if (start >= ft_strlen(s))
		return (ft_strnew(0));
	max_len = ft_strlen(s + start);
	if (len < max_len)
		max_len = len;
	return (ft_strndup(s + start, max_len));
}
