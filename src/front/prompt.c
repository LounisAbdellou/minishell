/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/02 15:31:04 by labdello          #+#    #+#             */
/*   Updated: 2024/09/12 18:58:42 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_current_path(char *home)
{
	size_t	len;
	char	*tmp;
	char	*path;
	char	cwd_buffer[PATH_MAX];

	len = 0;
	if (getcwd(cwd_buffer, sizeof(cwd_buffer)) == NULL)
		return (NULL);
	if (home != NULL)
		len = ft_strlen(home);
	if (len > 0 && ft_strncmp(cwd_buffer, home, len) == 0)
	{
		tmp = ft_strdup(cwd_buffer + (len - 1));
		if (!tmp)
			return (NULL);
		tmp[0] = '~';
	}
	else
		tmp = ft_strdup(cwd_buffer);
	if (!tmp)
		return (NULL);
	path = ft_strjoin(tmp, "$ ");
	free(tmp);
	return (path);
}

char	*get_station(char *session)
{
	char	*str;
	char	*user;
	char	**tab;
	char	*station;

	str = NULL;
	user = getenv("USER");
	if (!user)
		user = "John";
	if (session != NULL)
		str = ft_strchr(session, '/');
	if (str != NULL)
	{
		str[0] = '@';
		tab = ft_split(str, '.');
		if (!tab)
			return (NULL);
		station = ft_strjoin(user, tab[0]);
		ft_free_tab(tab);
	}
	else
		station = ft_strjoin_sep(user, "Doe", "@");
	return (station);
}

char	*get_prompt(char *station)
{
	char	*path;
	char	*prompt;

	path = get_current_path(getenv("HOME"));
	if (!path)
		return (NULL);
	prompt = ft_strjoin_sep(station, path, ":");
	free(path);
	return (prompt);
}
