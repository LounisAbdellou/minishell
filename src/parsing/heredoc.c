/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: labdello <labdello@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 17:48:46 by labdello          #+#    #+#             */
/*   Updated: 2024/09/20 13:46:03 by rbouselh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_line(char *line, int tmp_fd, t_env *env)
{
	size_t	i;
	size_t	flag;
	char	*var_name;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] == '$' && (ft_isalpha(line[i + 1]) || line[i + 1] == '_'))
		{
			i++;
			flag = i;
			while (line[i] != '\0' && (ft_isalnum(line[i]) || line[i] == '_'))
				i++;
			var_name = ft_strndup(line + flag, i - 1);
			ft_putstr_fd(ft_getenv(var_name, env->vars), tmp_fd);
			if (var_name)
				free(var_name);
		}
		else
		{
			ft_putchar_fd(line[i], tmp_fd);
			i++;
		}
	}
	ft_putchar_fd('\n', tmp_fd);
}

void	rl_heredoc(char *eof, t_env *env)
{
	int		fd;
	char	*line;

	signal(SIGINT, &heredoc_sig);
	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, eof) == 0)
		{
			free(line);
			exit(0);
		}
		fd = open("/tmp/.heredoc", O_RDWR | O_CREAT | O_APPEND, 0777);
		print_line(line, fd, env);
		close(fd);
		free(line);
	}
}

int	heredoc_fork(char *eof, int *status, t_env *env)
{
	int		pid;

	pid = fork();
	if (pid == -1)
		return (0);
	if (pid == 0)
	{
		close(env->fd_in);
		close(env->fd_out);
		rl_heredoc(eof, env);
	}
	waitpid(pid, status, 0);
	return (1);
}

int	here_doc(char *eof, t_env *env)
{
	int		fd;
	int		status;

	signal(SIGINT, SIG_IGN);
	if (access("/tmp/.heredoc", F_OK) == 0)
		unlink("/tmp/.heredoc");
	if (!heredoc_fork(eof, &status, env))
		return (-1);
	if (WIFEXITED(status))
		g_signal_status = WEXITSTATUS(status);
	signal(SIGINT, &readline_sig);
	fd = open("/tmp/.heredoc", O_RDWR);
	if (access("/tmp/.heredoc", F_OK | X_OK) == -1)
		return (close(fd), -1);
	return (fd);
}
