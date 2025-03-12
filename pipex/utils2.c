/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 17:32:52 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/24 17:12:16 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_all(char **mat, char *str)
{
	if (mat)
		ft_freemat((void **)mat, 2);
	if (str)
		free(str);
}

void	exit_error(char *msg, t_pipex **piper, char **cmd, char *path)
{
	ft_printfd(2, "%s\n", msg);
	if (piper)
	{
		if ((*piper)->fds)
		{
			if ((*piper)->i > 0)
				close_pipes((*piper)->fds, (*piper)->n_pipes);
			ft_freemat((void *)(*piper)->fds, (*piper)->n_pipes);
		}
		if ((*piper)->pids)
			free((*piper)->pids);
		free(*piper);
	}
	free_all(cmd, path);
	exit(1);
}

void	safe_close(int fd)
{
	if (fd != -1)
	{
		close(fd);
		fd = -1;
	}
}

void	close_all(int fd1, int fd2)
{
	safe_close(fd1);
	safe_close(fd2);
}

void	close_pipes(int **fds, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (fds[i])
			close_all(fds[i][0], fds[i][1]);
		i++;
	}
}
