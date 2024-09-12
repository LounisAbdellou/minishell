/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 15:18:52 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/10 15:17:30 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	is_sgl_token(char *input)
{
	if (input[0] == 40 || input[0] == 41)
		return (1);
	if (input[0] == '&' && input[1] != '&')
		return (1);
	if (input[0] == '|' && input[1] != '|')
		return (1);
	if (input[0] == '<' && input[1] != '<')
		return (1);
	if (input[0] == '>' && input[1] != '>')
		return (1);
	return (0);
}

int	is_dbl_token(char *input)
{
	if (input[0] == '&' && input[1] == '&')
		return (1);
	if (input[0] == '|' && input[1] == '|')
		return (1);
	if (input[0] == '<' && input[1] == '<')
		return (1);
	if (input[0] == '>' && input[1] == '>')
		return (1);
	return (0);
}

int	isnt_token_end(char *input)
{
	if (!input[0] || ft_isspace(input[0]))
		return (0);
	if (input[0] == 34 || input[0] == 39)
		return (1);
	if ((!input[1] || ft_isspace(input[1])) && input[0] != 34 && input[0] != 39)
		return (0);
	if (is_dbl_token(input + 1))
		return (0);
	if (is_dbl_token(input))
		return (1);
	if (is_sgl_token(input) || is_sgl_token(input + 1))
		return (0);
	return (1);
}

int	unclosed_q(char *token)
{
	int		i;
	int		open;
	char	sep;

	i = 0;
	open = 0;
	sep = 0;
	while (token[i])
	{
		if (!open && (token[i] == 34 || token[i] == 39))
		{
			open = 1;
			sep = token[i];
		}
		else if (open && token[i] == sep)
		{
			open = 0;
			sep = 0;
		}
		i++;
	}
	if (open)
		return (1);
	return (0);
}

int	is_end_join(char c, char sep)
{
	if (!c)
		return (1);
	if ((sep == 34 || sep == 39) && c == sep)
		return (1);
	else if ((sep != 34 && sep != 39) && (c == 34 || c == 39))
		return (1);
	return (0);
}
