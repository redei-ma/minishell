/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:28:54 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:29:11 by renato           ###   ########.fr       */
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
	if (shell->tok_type)
	{
		free(shell->tok_type);
		shell->tok_type = NULL;
	}
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
