/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 19:33:11 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 22:47:35 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_all_2(t_shell *shell)
{
	if (shell->env)
		ft_free_char_mat(shell->env);
	if (shell->input)
		free(shell->input);
	if (shell->tokens)
		ft_free_char_mat(shell->tokens);
}

void	free_all(t_shell *shell)
{
	t_cmd	*tmp;
	t_cmd	*tmp2;

	tmp = shell->cmds;
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
	if (shell->piper)
	{
		if (shell->piper->pids)
			free(shell->piper->pids);
		if (shell->piper->fds)
			ft_freemat((void **)shell->piper->fds, shell->piper->n_pipes);
		free(shell->piper);
	}
	free_all_2(shell);
}

void	close_all(t_shell *shell)
{
	int i;

	if (shell->piper)
	{
		i = 0;
		while (i < shell->piper->n_pipes)
		{
			safe_close(shell->piper->fds[i][0]);
			safe_close(shell->piper->fds[i][1]);
			i++;
		}
	}
	while (shell->cmds)
	{
		safe_close(shell->cmds->file_i);
		safe_close(shell->cmds->file_o);
		safe_close(shell->cmds->file_a);
		shell->cmds = shell->cmds->next;
	}
}

void	delete_heredoc(t_shell *shell)
{
	char	*filename;
	char	*num;
	int		i;

	i = 0;
	while (i <= shell->num_heredoc)
	{
		num = ft_itoa(i);
		if (!num)
		{
			ft_printfd(2, "Error: malloc failed\n");
			exit(1);
		}
		filename = ft_strjoin("heredoc_", num);
		free(num);
		if (!filename)
		{
			ft_printfd(2, "Error: malloc failed\n");
			exit(1);
		}
		unlink(filename);
		free(filename);
		i++;
	}
}

void	return_error(char *token, char *msg, t_shell *shell, int status)
{
	if (token)
		ft_printfd(2, "%s: %s\n", token, msg);
	else
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_all(shell);
	exit_status = status;
	return (status);
}

void exit_error(char *token, char *msg, t_shell *shell, int status)
{
	if (token)
		ft_printfd(2, "%s: %s\n", token, msg);
	else
		ft_printfd(2, "%s\n", msg);
	close_all(shell);
	delete_heredoc(shell);
	free_all(shell);
	exit_status = status;
	exit(status);
}
