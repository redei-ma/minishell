/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forking_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 19:26:04 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/25 16:23:57 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	middle_process(t_pipex **piper, char *av, int *fd_in, int *fd_out)
{
	safe_close(fd_in[1]);
	safe_close(fd_out[0]);
	if (dup2(fd_in[0], STDIN_FILENO) == -1
		|| dup2(fd_out[1], STDOUT_FILENO) == -1)
	{
		close_all(fd_in[0], fd_out[1]);
		exit_error("dup2 failed", piper, NULL, NULL);
	}
	close_all(fd_in[0], fd_out[1]);
	execute(piper, av, (*piper)->envp);
}

void	run_bonus(t_pipex **piper)
{
	int	i;

	i = 0;
	while (i < (*piper)->n_cmds)
	{
		(*piper)->pids[i] = fork();
		if ((*piper)->pids[i] == -1)
			exit_error("fork failed", piper, NULL, NULL);
		else if ((*piper)->pids[i] == 0)
		{
			close_unused_pipes(piper, i);
			if (i == 0)
				first_process(piper, (*piper)->fds[i]);
			else if (i == (*piper)->n_cmds - 1)
				last_process(piper, (*piper)->fds[i - 1]);
			else
				middle_process(piper, (*piper)->av[i + 2], (*piper)->fds[i - 1],
					(*piper)->fds[i]);
		}
		i++;
	}
}
