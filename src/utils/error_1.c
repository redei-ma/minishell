/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:33:11 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:28:49 by renato           ###   ########.fr       */
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

int	return_partial(char *msg, t_shell *shell, int status)
{
	if (msg)
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_part(shell);
	g_exit_status = status;
	return (status);
}

void	exit_partial(char *msg, t_shell *shell, int status)
{
	if (msg)
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_part(shell);
	g_exit_status = status;
	exit(status);
}

void	exit_all(char *msg, t_shell *shell, int status)
{
	if (msg)
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_all(shell);
	g_exit_status = status;
	exit(status);
}
