/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setter_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbouselh <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 16:34:38 by rbouselh          #+#    #+#             */
/*   Updated: 2024/09/13 19:40:34 by labdello         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	rl_heredoc(char *eof, int tmp_fd)
{
	char	*line;

	signal(SIGINT, &heredoc_sig);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof) == 0)
		{
			close(tmp_fd);
			free(line);
			exit(0);
		}
		ft_putendl_fd(line, tmp_fd);
		free(line);
	}
}

int	heredoc_fork(char *eof, int *status, t_env *env, int fd)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(env->fd_in);
		close(env->fd_out);
		rl_heredoc(eof, fd);
	}
	waitpid(pid, status, 0);
	return (1);
}

int	here_doc(char *eof, t_env *env)
{
	int		fd;
	int		status;

	signal(SIGINT, SIG_IGN);
	if (access("/tmp/.heredoc", F_OK | X_OK) == -1)
		unlink("/tmp/.heredoc");
	fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (!heredoc_fork(eof, &status, env, fd))
		return (close(fd), -1);
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	signal(SIGINT, &readline_sig);
	close(fd);
	fd = open("/tmp/.heredoc", O_RDWR);
	if (access("/tmp/.heredoc", F_OK | X_OK) == -1)
		return (close(fd), -1);
	return (fd);
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
