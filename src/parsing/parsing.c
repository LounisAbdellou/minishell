/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:38:16 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/13 18:10:09 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	should_parse(char *input)
{
	int	i;

	i = 0;
	if (!input || !input[0])
		return (0);
	if ((input[0] == '!' || input[0] == ':') && !input[1])
		return (0);
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (1);
		i++;
	}
	return (0);
}

int	parse_tree(t_word **tokens, t_operation **ops, t_env *env)
{
	t_operation	*new;
	t_word		*t;

	t = *tokens;
	new = ft_opnew(2);
	if (!new)
		return (0);
	*ops = new;
	while (t)
	{
		if (t->type == 8)
		{
			if (!generate_tree(t, ops, env))
				return (0);
			t = skip_parenthesis(t);
		}
		else if (t->type == 9)
			return (1);
		else if (!generate_tree(t, ops, env))
			return (0);
		t = t->next;
	}
	return (1);
}

int	analyze_syntax(t_word **lst)
{
	t_word	*t;
	int		open;
	int		close;

	t = *lst;
	open = 0;
	close = 0;
	while (t)
	{
		if (t->type == -1)
			return (printf("syntax error near : %s\n", t->content), 0);
		if (t->type > 5 && !analyze_token(t))
			return (0);
		if (t->type == 8)
			open++;
		if (t->type == 9)
			close++;
		if (open < close)
			return (printf("syntax error near : %s\n", t->content), 0);
		if (t->type == 0 && !transform_t(t))
			return (0);
		t = t->next;
	}
	return (1);
}

int	generate_token(char *str, int len, t_word **lst, t_env *env)
{
	char	*extract;
	char	*token;
	t_word	*new;
	int		type;
	int		s;

	s = 0;
	if (len > 1 && (str[len - 2] == 34 || str[len - 2] == 39)
		&& ft_isspace(str[len - 1]))
		s = 1;
	extract = ft_strndup(str, len - s);
	if (!extract)
		return (0);
	type = attribute_type(extract);
	token = get_token_content(extract, env);
	free(extract);
	if (!token)
		return (0);
	new = ft_wordnew(token);
	if (!new)
		return (free(token), 0);
	new->type = type;
	ft_wordadd_back(new, lst);
	return (1);
}

int	tokenize_input(char *input, t_word **lst, t_env *env)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	while (input[i])
	{
		while (input[i] && ft_isspace(input[i]))
			i++;
		if (!input[i])
			return (1);
		start = i;
		while (isnt_token_end(input + i))
			i += handle_quotes(input + i, input[i]);
		if (!generate_token(input + start, i - start + 1, lst, env))
			return (0);
		if (input[i])
			i++;
	}
	return (1);
}
