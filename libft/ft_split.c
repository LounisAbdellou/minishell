/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 00:11:11 by labdello          #+#    #+#             */
/*   Updated: 2024/05/29 17:25:09 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_word_count(char const *s, char c)
{
	size_t	i;
	size_t	count;

	i = 0;
	count = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		else
			i++;
	}
	return (count);
}

static void	*free_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i] != NULL)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	fill_tab(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	tab_i;
	size_t	flag;

	i = 0;
	tab_i = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			flag = i;
			while (s[i] != c && s[i] != '\0')
				i++;
			tab[tab_i] = ft_strndup(s + flag, i - flag);
			if (!tab[tab_i])
			{
				free_tab(tab);
				return (0);
			}
			tab_i++;
		}
		else
			i++;
	}
	return (1);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	tab = (char **) malloc(sizeof(char *) * (get_word_count(s, c) + 1));
	if (!tab || !s)
		return (NULL);
	tab[get_word_count(s, c)] = NULL;
	if (!fill_tab(tab, s, c))
		return (NULL);
	return (tab);
}
