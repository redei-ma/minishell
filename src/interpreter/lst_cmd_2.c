/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:40:38 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_fdout(char *token, char c, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (c == 'o')
		fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'a')
		fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		shell->cmds->skip = 1;
		ft_printfd(2, "minishell: %s: Error opening file\n", token);
	}
	shell->exit_status = 0;
	return (fd);
}

void	fileout_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;

	j = 0;
	while (tokens[*i][j] == '>')
		j++;
	if (!tokens[++(*i)])
		return ;
	if (shell->cmds->file_o != -1)
		safe_close(&shell->cmds->file_o);
	if (shell->cmds->file_a != -1)
		safe_close(&shell->cmds->file_a);
	if (j == 1)
		shell->cmds->file_o = handle_fdout(tokens[*i], 'o', shell);
	else if (j == 2)
		shell->cmds->file_a = handle_fdout(tokens[*i], 'a', shell);
}

int	handle_fdin(char *token, t_shell *shell)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
	{
		shell->cmds->skip = 1;
		ft_printfd(2, "minishell: %s: Error opening file\n", token);
	}
	shell->exit_status = 0;
	return (fd);
}

void	filein_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;

	j = 0;
	while (tokens[*i][j] == '<')
		j++;
	if (!tokens[++(*i)])
		return ;
	if (shell->cmds->file_i != -1)
		safe_close(&shell->cmds->file_i);
	if (j == 1)
		shell->cmds->file_i = handle_fdin(tokens[*i], shell);
	else if (j == 2)
		shell->cmds->file_i = handle_heredoc(tokens[*i], shell);
}

void	pipe_manager(t_shell *shell, char **tokens, int *i)
{
	t_pipex	*piper;

	piper = shell->piper;
	if (tokens[*i + 1])
	{
		shell->cmds->next = ft_newcmd(shell);
		piper->fds = ft_realloc(piper->fds, (piper->n_pipes + 1)
				* sizeof(int [2]), (piper->n_pipes + 2) * sizeof(int [2]));
		if (!piper->fds)
			exit_all("Error: malloc failed\n", shell, 1);
		if (pipe(piper->fds[piper->n_pipes]) < 0)
			exit_all("Error: pipe failed\n", shell, 1);
		if (shell->cmds->file_o == -1)
			shell->cmds->file_o = piper->fds[piper->n_pipes][1];
		shell->cmds->next->file_i = piper->fds[piper->n_pipes][0];
		piper->n_pipes++;
		shell->cmds = shell->cmds->next;
	}
}
