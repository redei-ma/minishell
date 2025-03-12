/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/20 12:28:16 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/24 17:06:01 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	close_unused_pipes(t_pipex **piper, int i)
{
	int	j;

	j = 0;
	while (j < (*piper)->n_pipes)
	{
		if ((i == 0 && j != 0))
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		else if (i == (*piper)->n_pipes && j != (*piper)->n_pipes - 1)
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		else if (j != i && j != i - 1)
			close_all((*piper)->fds[j][0], (*piper)->fds[j][1]);
		j++;
	}
}

void	exit_heredoc(t_pipex **piper)
{
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
	exit(0);
}
