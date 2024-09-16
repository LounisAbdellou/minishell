/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:38 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/20 18:15:41 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static void	set_file_err(t_file *f, int fd, t_env *env)
{
	if (fd == -1 || env->is_err > 0)
		return ;
	if (access(f->name, F_OK) == -1)
	{
		env->is_err++;
		print_blt_err(NULL, NULL, "No such file or directory", 0);
	}
	else if (f->type == 12 && access(f->name, R_OK) == -1)
	{
		env->is_err++;
		print_blt_err(NULL, NULL, "Permission denied", 0);
	}
	else if ((f->type == 11 || f->type == 13) && access(f->name, W_OK) == -1)
	{
		env->is_err++;
		print_blt_err(NULL, NULL, "Permission denied", 0);
	}
}

int	set_file(t_file *current, t_env *env)
{
	int		fd;
	int		tmp;

	fd = -2;
	tmp = -2;
	while (current)
	{
		if (tmp > 1)
			close(tmp);
		set_file_err(current, fd, env);
		if (current->type == 14)
			tmp = here_doc(current->name, env);
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
		return (tmp);
	return (close(tmp), fd);
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
