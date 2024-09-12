/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:38 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/11 19:50:12 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	here_doc(char *eof)
{
	(void)eof;
	return (0);
}

// int	handle_here_doc(char *eof, t_cmd *cmd)
// {
// 	int	fd;
//
// 	fd = here_doc(eof);
// 	if (cmd->to_read == -1 && fd > 1)
// 	{
// 		close(fd);
// 		return (cmd->to_read);
// 	}
// 	if (cmd->to_read > 1)
// 		close(cmd->to_read);
// 	return (fd);
// }

int	set_file(t_file *current)
{
	int		fd;
	int		tmp;

	fd = -2;
	tmp = -2;
	while (current)
	{
		if (tmp > 1)
			close(tmp);
		if (current->type == 14)
			tmp = here_doc(current->name);
		else if (fd != -1 && current->type == 12)
			tmp = open(current->name, O_RDONLY);
		else if (fd != -1 && current->type == 11)
			tmp = open(current->name, O_CREAT | O_RDWR | O_TRUNC, 0644);
		else if (fd != -1 && current->type == 13)
			tmp = open(current->name, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (tmp == -1)
			fd = tmp;
		current = current->next;
	}
	if (fd != -1)
		fd = tmp;
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
