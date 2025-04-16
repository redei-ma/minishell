/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:14:06 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	process_heredoc_line(int *fd, char *key, t_shell *shell)
{
	char	*line;

	signal(SIGINT, handle_ctrl_c_get);
	line = readline("> ");
	if (g_exit_status == 130)
	{
		close(*fd);
		unlink(shell->heredocs[shell->num_heredoc - 1]);
		*fd = open(shell->heredocs[shell->num_heredoc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		shell->trigger = 1;
		return (0);
	}
	if (!line)
	{
		if (g_exit_status != 130)  // Solo se non è stato un Ctrl+C
			ft_printfd(2, "minishell: warning: here-document delimited by end-of-file (wanted `%s')\n", key);
		shell->trigger = (g_exit_status == 130) ? 1 : 2;
		return (0);
	}
	if (ft_strncmp(line, key, ft_strlen(key)) == 0)
		return (free(line), 0);
	line = expander(line, shell, 1);
	if (!line)
		exit_all("Error: malloc failed\n", shell, 1);
	ft_printfd(*fd, "%s\n", line);
	free(line);
	return (1);
}

int	handle_heredoc(char *token, t_shell *shell)
{
	int		fd;
	char	*filename;

	filename = search_name(shell);
	shell->heredocs = ft_realloc(shell->heredocs, (shell->num_heredoc + 1) *
		sizeof(char *), (shell->num_heredoc + 2) * sizeof(char *));
	if (!shell->heredocs)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->heredocs[shell->num_heredoc] = filename;
	shell->num_heredoc++;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		ft_printfd(2, "minishell: %s: No such file or directory\n", token);
		return (shell->cmds->skip = 1, -1);
	}
	while (process_heredoc_line(&fd, token, shell))
		;
	signal(SIGINT, handle_ctrl_c);
	close(fd);
	if (shell->trigger)
		return (-1);
	fd = handle_fdin(filename, shell);
	return (fd);
}

void	fileout_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;

	j = 0;
	while (tokens[*i][j] == '>')
		j++;
	if (j == 1 && tokens[++(*i)])
		shell->cmds->file_o = handle_fdout(tokens[*i], 'o', shell);
	else if (j == 2 && tokens[++(*i)])
		shell->cmds->file_a = handle_fdout(tokens[*i], 'a', shell);
	// else
	// 	shell->trigger = 1;
}

void	filein_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;

	j = 0;
	while (tokens[*i][j] == '<')
		j++;
	if (j == 1 && tokens[++(*i)])
		shell->cmds->file_i = handle_fdin(tokens[*i], shell);
	else if (j == 2 && tokens[++(*i)])
		shell->cmds->file_i = handle_heredoc(tokens[*i], shell);
	// else
	// 	shell->trigger = 1;
}
