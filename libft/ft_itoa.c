/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 11:48:29 by labdello          #+#    #+#             */
/*   Updated: 2024/05/29 17:23:25 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h" 

static void	fill_nbr(int nbr, char *str)
{
	int				r;
	size_t			i;
	unsigned int	nb;

	i = 0;
	nb = ft_abs(nbr);
	while (nb)
	{
		r = nb % 10;
		str[i++] = r + 48;
		nb = nb / 10;
	}
	if (nbr < 0)
		str[i++] = '-';
	else if (nbr == 0)
		str[i++] = '0';
	str[i] = '\0';
	ft_strrev(str);
}

char	*ft_itoa(int n)
{
	size_t	nbr_len;
	char	*str;

	nbr_len = ft_nbrlen(n);
	str = (char *) malloc(sizeof(char) * (nbr_len + 1));
	if (!str)
		return (NULL);
	fill_nbr(n, str);
	return (str);
}
