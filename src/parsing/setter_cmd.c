/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 12:45:20 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/05 17:11:35 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static int	get_type_cmd(char *content)
{
	if (!ft_strcmp(content, "echo"))
		return (0);
	if (!ft_strcmp(content, "cd"))
		return (0);
	if (!ft_strcmp(content, "unset"))
		return (0);
	if (!ft_strcmp(content, "export"))
		return (0);
	if (!ft_strcmp(content, "exit"))
		return (0);
	if (!ft_strcmp(content, "pwd"))
		return (0);
	if (!ft_strcmp(content, "env"))
		return (0);
	return (1);
}

static char	*get_path_cmd(char *content, t_cmd *cmd)
{
	char	*str;
	char	**path;
	int		i;

	str = getenv("PATH");
	if (!str || cmd->type == 0 || access(content, X_OK) == 0 || !content[0])
		return (content);
	str = ft_strdup(str);
	if (!str)
		return (NULL);
	path = ft_split(str, ':');
	if (!path)
		return (free(str), NULL);
	i = 0;
	while (path[i])
	{
		if (check_cmd_path(&str, path[i], content))
		{
			free(content);
			content = str;
			return (ft_free_tab(path), content);
		}
		i++;
	}
	return (free_tab_str(path, str), content);
}

int	set_file_cmd(t_word *t, t_cmd *cmd)
{
	int		fd;
	char	*content;

	content = t->next->content;
	fd = -1;
	if (t->type == 14)
		fd = here_doc(content);
	else if (t->type == 13)
		fd = open(content, O_CREAT | O_RDWR | O_APPEND, 0644);
	else if (t->type == 12)
		fd = open(content, O_RDONLY);
	else if (t->type == 11)
		fd = open(content, O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (fd == -1 && t->type == 14)
		return (0);
	else if (t->type == 13 || t->type == 11)
		cmd->to_write = fd;
	else if (t->type == 14 || t->type == 12)
		cmd->to_read = fd;
	return (1);
}

int	set_arg_cmd(t_word *t, t_cmd *cmd)
{
	char	*content;
	char	**args;
	int		i;

	i = 0;
	content = ft_strdup(t->content);
	if (!content)
		return (0);
	args = ft_calloc(ft_tablen(cmd->args) + 2, sizeof(char *));
	if (!args)
		return (free(content), 0);
	while (cmd->args && cmd->args[i])
	{
		args[i] = ft_strdup(cmd->args[i]);
		if (!args[i])
			return (free_tab_str(args, content), 0);
		i++;
	}
	args[i] = content;
	if (cmd->args)
		ft_free_tab(cmd->args);
	cmd->args = args;
	return (1);
}

int	set_path_cmd(t_word *t, t_cmd *cmd)
{
	char	*content;

	content = ft_strdup(t->content);
	if (!content)
		return (0);
	cmd->type = get_type_cmd(content);
	cmd->path = get_path_cmd(content, cmd);
	if (!cmd->path)
		return (0);
	cmd->args = ft_calloc(2, sizeof(char *));
	if (!cmd->args)
		return (0);
	cmd->args[0] = ft_strdup(cmd->path);
	if (!cmd->args[0])
		return (0);
	return (1);
}
