/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 14:14:27 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/13 15:00:08 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	handle_quotes(char *input, char c)
{
	int	i;

	i = 1;
	if (c != '\'' && c != '\"')
		return (i);
	while (input[i] != '\0' && input[i] != c)
		i++;
	if (input[i])
		return (i + 1);
	return (i);
}

int	transform_t(t_word *token)
{
	t_word	*current;

	current = token;
	current->type = 1;
	current = current->next;
	while (current && current->type == 0)
	{
		current->type = 2;
		current = current->next;
	}
	return (1);
}

int	attribute_type(char *token)
{
	if ((!ft_strcmp(token, "&") && ft_strlen(token) == 1) || unclosed_q(token))
		return (-1);
	if (!ft_strcmp(token, "&&") && ft_strlen(token) == 2)
		return (6);
	if (!ft_strcmp(token, "||") && ft_strlen(token) == 2)
		return (7);
	if (!ft_strcmp(token, "(") && ft_strlen(token) == 1)
		return (8);
	if (!ft_strcmp(token, ")") && ft_strlen(token) == 1)
		return (9);
	if (!ft_strcmp(token, "|") && ft_strlen(token) == 1)
		return (10);
	if (!ft_strcmp(token, ">") && ft_strlen(token) == 1)
		return (11);
	if (!ft_strcmp(token, "<") && ft_strlen(token) == 1)
		return (12);
	if (!ft_strcmp(token, ">>") && ft_strlen(token) == 2)
		return (13);
	if (!ft_strcmp(token, "<<") && ft_strlen(token) == 2)
		return (14);
	return (0);
}

static int	join_expand(char **token, char *str, char sep, t_env *env)
{
	char	*extract;
	char	*expand;
	char	*join;
	int		i;

	i = 1;
	while (str[i] && !is_end_join(str[i], sep))
		i++;
	if (i - env->s_expand == 0)
		return (1);
	extract = ft_strndup(str + env->s_expand, i - env->s_expand);
	if (!extract)
		return (0);
	expand = extract;
	if (sep != 39)
		expand = handle_expand(extract, env);
	if (!expand)
		return (free(extract), 0);
	join = ft_strjoin(*token, expand);
	free(expand);
	if (!join)
		return (0);
	free(*token);
	*token = join;
	return (1);
}

char	*get_token_content(char *str, t_env *env)
{
	char	*token;
	char	sep;
	int		i;

	token = ft_calloc(1, sizeof(char));
	if (!token)
		return (NULL);
	i = 0;
	while (str[i])
	{
		sep = str[i];
		env->s_expand = 0;
		if (sep == 34 || sep == 39)
			env->s_expand = 1;
		if (!join_expand(&token, str + i, sep, env))
			return (free(token), NULL);
		i++;
		while (str[i] && !is_end_join(str[i], sep))
			i++;
		if (str[i] && (sep == 34 || sep == 39))
			i++;
	}
	return (token);
}
