/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 14:55:43 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/25 16:21:40 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include <sys/wait.h>

void	here_process(t_pipex **piper, int *fd)
{
	char	*line;
	char	*limiter;

	safe_close(fd[0]);
	limiter = ft_strjoin((*piper)->av[2], "\n");
	while (1)
	{
		ft_printfd(1, "> ");
		line = get_next_line(0);
		if (!line)
		{
			free(limiter);
			exit_error("get_next_line failed", piper, NULL, NULL);
		}
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
			break ;
		ft_printfd(fd[1], "%s", line);
		free(line);
	}
	if (line)
		free(line);
	free(limiter);
	safe_close(fd[1]);
	exit_heredoc(piper);
}

void	run_heredoc(t_pipex **piper)
{
	int	i;

	i = 0;
	(*piper)->flag = 1;
	while (i < (*piper)->n_cmds)
	{
		(*piper)->pids[i] = fork();
		if ((*piper)->pids[i] == -1)
			exit_error("fork failed", piper, NULL, NULL);
		else if ((*piper)->pids[i] == 0)
		{
			close_unused_pipes(piper, i);
			if (i == 0)
				here_process(piper, (*piper)->fds[i]);
			else if (i == (*piper)->n_cmds - 1)
				last_process(piper, (*piper)->fds[i - 1]);
			else
				middle_process(piper, (*piper)->av[i + 2], (*piper)->fds[i - 1],
					(*piper)->fds[i]);
		}
		if (i == 0)
			wait(NULL);
		i++;
	}
}
