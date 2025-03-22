/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:23:27 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/22 19:49:05 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
	if (shell->env)
		ft_free_char_mat(shell->env);
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

int	ft_cmd_size(t_cmd *lst)
{
	t_cmd	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}
