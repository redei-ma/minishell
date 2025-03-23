/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by renato            #+#    #+#             */
/*   Updated: 2025/03/23 00:54:31 by renato           ###   ########.fr       */
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
		return_error("open faild", shell, 1);
		//non sono sicuro quale messaggio mettere
		// if (errno == EACCES)
		// 	return_error("Error: permission denied\n", shell, 13);
		// else if (errno == ENOENT)
		// 	return_error("Error: file not found\n", shell, 2);
		// else if (errno == EISDIR)
		// 	return_error("Error: is a directory\n", shell, 126);
		// else if (errno == 	ENOSPC)
		// 	return_error("Error: no space left on device\n", shell, 28);
		// else if (errno == EROFS)
		// 	return_error("Error: read-only file system\n", shell, 30);
		// else
		// 	return_error("Error: failed to open file\n", shell, 1);
	}
	return (fd);
}

int	handle_fdin(char *token, t_shell *shell)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
	{
		//non sono sicuro dquale messaggio stamapre
		return_error("open faild", shell, 1);
	}
	return fd;
}

char	*search_name(t_shell *shell)
{
	char	*filename;
	char	*num;

	while (1)
	{
		num = ft_itoa(shell->num_heredoc);
		if (!num)
			exit_error("Error: malloc failed\n", shell, 1);
		filename = ft_strjoin("heredoc_", num);
		if (!filename)
		{
			free(num);
			exit_error("Error: malloc failed\n", shell, 1);
		}
		free(num);
		shell->num_heredoc++;
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
	}
	return (filename);
}

int process_heredoc_line(int fd, char *limiter)
{
	char	*line;

	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (!line)
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		return (free(line), 0);
	ft_printfd(fd, "%s", line);
	free(line);
	return (1);
}

int	handle_heredoc(char *token, t_shell *shell)
{
	int		fd;
	char	*limiter;
	char	*filename;

	filename = search_name(shell);
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		//return_error();
		exit(1);
	limiter = ft_strjoin(token, "\n");
	if (!limiter)
		exit_error("Error: malloc failed\n", shell, 1);
	while (process_heredoc_line(fd, limiter))
		;
	free(limiter);
	close(fd);
	fd = handle_fdin(filename, shell);
	free(filename);
	return (fd);
}
