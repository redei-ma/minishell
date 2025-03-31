/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by renato            #+#    #+#             */
/*   Updated: 2025/03/31 15:20:07 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_fdout(char *token, char c, t_shell *shell)
{
	int	fd;

	fd = -1;
	if (c == 'o')
		fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'a')
		fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		shell->trigger = 1;
		exit_partial("open faild", shell, 1);
	}
	return (fd);
}

int	handle_fdin(char *token, t_shell *shell)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
	{
		shell->trigger = 1;
		return_partial("open faild", shell, 1);
	}
	return (fd);
}

char	*search_name(t_shell *shell)
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

int	process_heredoc_line(int fd, char *limiter, t_shell *shell)
{
	char	*line;

	signal(SIGINT, handle_ctrl_c_get);
	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (g_exit_status == 130)
	{
		if (line)
			free(line);
		dup2(shell->original_stdin, 0);
		shell->trigger = 1;
		return (0);
	}
	if (!line)
		return (0);
		// forse e ctrl
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		return (free(line), 0);
	ft_printfd(fd, "%s", line);
	free(line);
	signal(SIGINT, handle_ctrl_c);
	return (1);
}

int	handle_heredoc(char *token, t_shell *shell)
{
	int		fd;
	char	*limiter;
	char	*filename;

	filename = search_name(shell);
	shell->heredocs = ft_realloc(shell->heredocs, (shell->num_heredoc + 1) * sizeof(char *), (shell->num_heredoc + 2) * sizeof(char *));
	if (!shell->heredocs)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->heredocs[shell->num_heredoc] = filename;
	shell->num_heredoc++;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		shell->trigger = 1;
		ft_printfd(2, "minishell: %s: No such file or directory\n", token);
		return (-1);
	}
	limiter = ft_strjoin(token, "\n");
	if (!limiter)
		exit_all("Error: malloc failed\n", shell, 1);
	while (process_heredoc_line(fd, limiter, shell))
		;
	free(limiter);
	close(fd);
	if (shell->trigger)
		return (-1);
	fd = handle_fdin(filename, shell);
	return (fd);
}
