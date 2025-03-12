/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:16:38 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/02 17:51:09 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*already_path(char *cmd)
{
	char	*path;

	path = ft_strdup(cmd);
	if (!path)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

void	execute(t_pipex **piper, char *av, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(av, ' ');
	if (!cmd)
		exit_error("ft_split failed", piper, NULL, NULL);
	if (cmd[0][0] == '/')
		path = already_path(cmd[0]);
	else
		path = get_path(cmd[0], envp);
	if (!path)
		exit_error("cmd not found", piper, cmd, NULL);
	execve(path, cmd, envp);
	exit_error("execve failed", piper, cmd, path);
}

void	last_process(t_pipex **piper, int *fd)
{
	int		fd_out;
	int		pos;

	safe_close(fd[1]);
	pos = (*piper)->ac - 1;
	if ((*piper)->flag == 1)
		fd_out = open((*piper)->av[pos], O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd_out = open((*piper)->av[pos], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		safe_close(fd[0]);
		exit_error("outfile permission denied", piper, NULL, NULL);
	}
	if (dup2(fd[0], STDIN_FILENO) == -1
		|| dup2(fd_out, STDOUT_FILENO) == -1)
	{
		close_all(fd_out, fd[0]);
		exit_error("dup2 failed", piper, NULL, NULL);
	}
	close_all(fd_out, fd[0]);
	execute(piper, (*piper)->av[pos - 1], (*piper)->envp);
}

void	first_process(t_pipex **piper, int *fd)
{
	int		fd_in;

	safe_close(fd[0]);
	fd_in = open((*piper)->av[1], O_RDONLY);
	if (fd_in == -1)
	{
		safe_close(fd[1]);
		exit_error("infile permission denied", piper, NULL, NULL);
	}
	if (dup2(fd_in, STDIN_FILENO) == -1
		|| dup2(fd[1], STDOUT_FILENO) == -1)
	{
		close_all(fd_in, fd[1]);
		exit_error("dup2 failed", piper, NULL, NULL);
	}
	close_all(fd_in, fd[1]);
	execute(piper, (*piper)->av[2], (*piper)->envp);
}

void	run(t_pipex **piper)
{
	(*piper)->pids[0] = fork();
	if ((*piper)->pids[0] == -1)
		exit_error("fork failed", piper, NULL, NULL);
	else if ((*piper)->pids[0] == 0)
		first_process(piper, (*piper)->fds[0]);
	(*piper)->pids[1] = fork();
	if ((*piper)->pids[1] == -1)
		exit_error("fork failed", piper, NULL, NULL);
	else if ((*piper)->pids[1] == 0)
		last_process(piper, (*piper)->fds[0]);
}
