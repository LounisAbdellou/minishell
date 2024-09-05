/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/25 16:09:33 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/04 16:51:03 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static char	*get_extract(char *str, int n, int is_env)
{
	char	*extract;
	char	*var_name;

	extract = ft_strndup(str, n);
	var_name = NULL;
	if (!extract)
		return (NULL);
	if (is_env)
	{
		var_name = extract;
		extract = getenv(var_name + 1);
		if (extract)
			extract = ft_strdup(extract);
		free(var_name);
		if (!extract)
			extract = ft_strdup("");
		if (!extract)
			return (NULL);
	}
	return (extract);
}

static int	extract_and_join(char *str, char **content, int n, int is_env)
{
	char	*extract;
	char	*new_content;

	if (!(*content))
	{
		*content = get_extract(str, n, is_env);
		if (!(*content))
			return (0);
		return (1);
	}
	extract = get_extract(str, n, is_env);
	if (!extract)
		return (0);
	new_content = ft_strjoin(*content, extract);
	free(extract);
	if (!new_content)
		return (0);
	free(*content);
	*content = new_content;
	return (1);
}

static int	is_end_expand(char *str, int is_env)
{
	if (is_env && (ft_isspace(str[0]) || str[0] == '\0'
			|| str[0] == '$' || str[0] == 39))
		return (1);
	if (!is_env && (str[0] == '$' || str[0] == '\0'))
		return (1);
	return (0);
}

char	*handle_empty(char *content)
{
	if (!content)
		content = ft_calloc(1, sizeof(char));
	if (!content)
		return (NULL);
	return (content);
}

char	*handle_expand(char *str)
{
	char	*content;
	int		is_env;
	int		i;
	int		s;

	i = 0;
	s = 0;
	is_env = 0;
	content = NULL;
	while (str[s])
	{
		if (str[s] == '$' && str[s + 1] != '\0' && !ft_isspace(str[s + 1]))
		{
			is_env = 1;
			i++;
		}
		while (!is_end_expand(str + i, is_env))
			i++;
		if (!extract_and_join(str + s, &content, i - s, is_env))
			return (NULL);
		s = i;
		i++;
		is_env = 0;
	}
	return (free(str), handle_empty(content));
}
