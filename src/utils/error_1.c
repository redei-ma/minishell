/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:33:11 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:41:04 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	delete_heredoc(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->heredocs)
	{
		while (shell->heredocs[i])
		{
			unlink(shell->heredocs[i]);
			free(shell->heredocs[i]);
			i++;
		}
		free(shell->heredocs);
		shell->heredocs = NULL;
	}
}

void	close_all(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->piper)
	{
		while (i < shell->piper->n_pipes)
		{
			safe_close(&shell->piper->fds[i][0]);
			safe_close(&shell->piper->fds[i][1]);
			i++;
		}
	}
	shell->cmds = shell->head;
	while (shell->cmds)
	{
		safe_close(&shell->cmds->file_i);
		safe_close(&shell->cmds->file_o);
		safe_close(&shell->cmds->file_a);
		shell->cmds = shell->cmds->next;
	}
}

int	return_partial(char *msg, t_shell *shell, int stat)
{
	if (msg)
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_part(shell);
	shell->exit_status = stat;
	return (stat);
}

void	exit_all(char *msg, t_shell *shell, int stat)
{
	if (msg)
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_all(shell);
	exit(stat);
}
