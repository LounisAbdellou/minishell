/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:38 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/09 12:29:47 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc(char *eof)
{
	(void)eof;
	return (0);
}

int	handle_here_doc(char *eof, t_cmd *cmd)
{
	int	fd;

	fd = here_doc(eof);
	if (cmd->to_read == -1 && fd > 1)
	{
		close(fd);
		return (cmd->to_read);
	}
	if (cmd->to_read > 1)
		close(cmd->to_read);
	return (fd);
}

int	get_fd_cmd(t_word *t, char *file, t_cmd *cmd)
{
	int	fd;

	fd = -2;
	if (t->type == 14)
		fd = handle_here_doc(file, cmd);
	else if (t->type == 13 || t->type == 11)
	{
		if (cmd->to_write > 1)
			close(cmd->to_write);
		if (t->type == 13)
			fd = open(file, O_CREAT | O_RDWR | O_APPEND, 0644);
		else
			fd = open(file, O_CREAT | O_RDWR | O_TRUNC, 0644);
	}
	else if (t->type == 12 || t->type == 14)
	{
		if (cmd->to_read == -1)
			return (cmd->to_read);
		if (cmd->to_read > 1)
			close(cmd->to_read);
		if (t->type == 12)
			fd = open(file, O_RDONLY);
	}
	return (fd);
}

int	check_cmd_path(char **str, char *path, char *exec)
{
	char	*tmp;
	char	*content;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (0);
	content = ft_strjoin(tmp, exec);
	free(tmp);
	if (!content)
		return (0);
	if (access(content, X_OK) == 0)
	{
		free(*str);
		*str = content;
		return (1);
	}
	free(content);
	return (0);
}
