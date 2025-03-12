/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:50:07 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/24 13:04:49 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

int	main(int ac, char **av, char **envp)
{
	t_pipex	*piper;
	int		i;

	if (ac < 5)
		return (ft_printfd(2, "Input: <infile> <cmd1> ... <cmdN> <outfile>\n"));
	if (!envp)
		return (ft_printfd(2, "envp not found"));
	i = 0;
	piper = ft_calloc(1, sizeof(t_pipex));
	if (!piper)
		return (ft_printfd(2, "malloc failed"));
	set_piper(&piper, ac, av, envp);
	if (ft_strncmp(av[1], "here_doc", 8) == 0)
		run_heredoc(&piper);
	else
		run_bonus(&piper);
	close_pipes(piper->fds, piper->n_pipes);
	ft_freemat((void *)piper->fds, piper->n_pipes);
	free(piper->pids);
	free(piper);
	while (wait(NULL) > 0)
		;
	return (0);
}
