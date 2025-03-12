/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 16:45:14 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/24 12:58:29 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*piper;

	if (ac != 5)
		return (ft_printfd(2, "Input: <infile> <cmd1> <cmd2> <outfile>\n"));
	if (!envp)
		return (ft_printfd(2, "envp not found"));
	piper = ft_calloc(1, sizeof(t_pipex));
	if (!piper)
		return (ft_printfd(2, "malloc failed"));
	set_piper(&piper, ac, av, envp);
	run(&piper);
	close_pipes(piper->fds, piper->n_pipes);
	ft_freemat((void *)piper->fds, piper->n_pipes);
	free(piper->pids);
	free(piper);
	while (wait(NULL) > 0)
		;
	return (0);
}
