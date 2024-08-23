/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 18:23:03 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/04 16:40:30 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	free_parse(t_word **token, t_operation **operations)
{
	free_words(token);
	free_operations(operations);
	return ;
}

void	free_tab_str(char **tab, char *str)
{
	if (tab)
		ft_free_tab(tab);
	if (str)
		free(str);
}
