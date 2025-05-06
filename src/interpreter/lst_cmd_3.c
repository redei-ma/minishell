/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:51:12 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:40:54 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_ctrl_c_or_eof(int *fd, char *key, t_shell *shell, char *line)
{
	if (g_signal == 130)
	{
		g_signal = 0;
		close(*fd);
		unlink(shell->heredocs[shell->num_heredoc - 1]);
		*fd = open(shell->heredocs[shell->num_heredoc - 1],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
		shell->trigger = 130;
		return (0);
	}
	if (!line)
	{
		ft_printfd(2, "minishell: warning: here-document delimited by \
end-of-file (wanted `%s')\n", key);
		return (0);
	}
	return (1);
}

static int	process_heredoc_line(int *fd, char *key, t_shell *shell)
{
	char	*line;

	signal(SIGINT, handle_ctrl_c_get);
	line = readline("> ");
	if (!handle_ctrl_c_or_eof(fd, key, shell, line))
		return (0);
	if (ft_strcmp(line, key) == 0)
		return (free(line), 0);
	line = expander_hd(line, shell);
	if (!line)
		exit_all("Error: malloc failed\n", shell, 1);
	ft_printfd(*fd, "%s\n", line);
	free(line);
	return (1);
}

static char	*search_name(t_shell *shell)
{
	char	*filename;
	char	*num;
	int		i;

	i = 0;
	while (1)
	{
		num = ft_itoa(i);
		if (!num)
			exit_all("Error: malloc failed\n", shell, 1);
		filename = ft_strjoin("heredoc_", num);
		if (!filename)
		{
			free(num);
			exit_all("Error: malloc failed\n", shell, 1);
		}
		free(num);
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		i++;
	}
	return (filename);
}

int	handle_heredoc(char *token, t_shell *shell)
{
	int		fd;
	char	*filename;

	filename = search_name(shell);
	shell->heredocs = ft_realloc(shell->heredocs, (shell->num_heredoc + 1)
			* sizeof(char *), (shell->num_heredoc + 2) * sizeof(char *));
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
	shell->exit_status = 0;
	while (process_heredoc_line(&fd, token, shell))
		;
	signal(SIGINT, handle_ctrl_c);
	close(fd);
	if (shell->trigger)
		return (-1);
	fd = handle_fdin(filename, shell);
	return (fd);
}
