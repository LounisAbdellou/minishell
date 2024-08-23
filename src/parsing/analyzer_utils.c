/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/23 19:45:39 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/02 19:39:56 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	analyze_operator(t_word *token)
{
	if (!token->next || !token->prev)
		return (printf("syntax error near : %s\n", token->content), 0);
	if (token->next && token->next->type == 6)
		return (printf("syntax error near : %s\n", token->next->content), 0);
	if (token->next && token->next->type == 7)
		return (printf("syntax error near : %s\n", token->next->content), 0);
	if (token->next && token->next->type == 10)
		return (printf("syntax error near : %s\n", token->next->content), 0);
	if (token->next && token->next->type == 9)
		return (printf("syntax error near : %s\n", token->next->content), 0);
	return (1);
}

int	analyze_redirect(t_word *token)
{
	if (!token->next)
		return (printf("syntax error near : %s\n", token->content), 0);
	if (token->next && token->next->type != 0)
		return (printf("syntax error near : %s\n", token->next->content), 0);
	token->next->type = 3;
	return (1);
}

int	analyze_par(t_word *token)
{
	if (token->type == 8 && !token->next)
		return (printf("syntax error near : %s\n", token->content), 0);
	if (token->type == 9 && !token->prev)
		return (printf("syntax error near : %s\n", token->content), 0);
	if (token->type == 8 && (token->next->type != 0 && token->next->type < 11))
		return (printf("syntax error near : %s\n", token->next->content), 0);
	if (token->type == 9 && !token->next)
		return (1);
	if (token->type == 9 && (token->next->type == 0 || token->next->type == 8))
		return (printf("syntax error near : %s\n", token->next->content), 0);
	return (1);
}

int	analyze_closure(t_word *token)
{
	t_word	*current;
	int		open;
	int		close;

	current = token->next;
	open = 1;
	close = 0;
	while (current)
	{
		if (current->type == 8)
			open++;
		if (current->type == 9)
			close++;
		if (open && open == close)
			return (1);
		current = current->next;
	}
	return (0);
}

int	analyze_token(t_word *t)
{
	if ((t->type == 6 || t->type == 7 || t->type == 10) && !analyze_operator(t))
		return (0);
	if ((t->type >= 11 && t->type <= 14) && !analyze_redirect(t))
		return (0);
	if ((t->type == 8 || t->type == 9) && !analyze_par(t))
		return (0);
	if ((t->type == 8) && !analyze_closure(t))
		return (printf("syntax error near : %s\n", t->content), 0);
	return (1);
}
