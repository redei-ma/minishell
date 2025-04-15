/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:33:11 by renato            #+#    #+#             */
/*   Updated: 2025/04/14 12:26:08 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_part_2(t_shell *shell)
{
	if (shell->piper)
	{
		if (shell->piper->pids)
		{
			free(shell->piper->pids);
			shell->piper->pids = NULL;
		}
		if (shell->piper->fds)
		{
			free(shell->piper->fds);
			shell->piper->fds = NULL;
		}
	}
	if (shell->input)
	{
		free(shell->input);
		shell->input = NULL;
	}
	if (shell->tokens)
	{
		ft_free_char_mat(shell->tokens);
		shell->tokens = NULL;
	}
}

void	free_part(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = shell->head;
	while (tmp)
	{
		tmp2 = tmp->next;
		if (tmp->cmd)
			free(tmp->cmd);
		if (tmp->args)
			ft_free_char_mat(tmp->args);
		free(tmp);
		tmp = tmp2;
	}
	shell->head = NULL;
	free_part_2(shell);
}

void	free_all(t_shell *shell)
{
	free_part(shell);
	delete_heredoc(shell);
	if (shell->env)
	{
		ft_free_char_mat(shell->env);
		shell->env = NULL;
	}
	if (shell->piper)
	{
		free(shell->piper);
		shell->piper = NULL;
	}
	free(shell);
	shell = NULL;
}

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
	//ft_printfd(2, "%d", g_exit_status);
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
