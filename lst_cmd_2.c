/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by renato            #+#    #+#             */
/*   Updated: 2025/03/26 17:43:41 by redei-ma         ###   ########.fr       */
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
		exit_partial("open faild", shell, 1);
		//non sono sicuro quale messaggio mettere
		// if (errno == EACCES)
		// 	return_msg("Error: permission denied\n", shell, 13);
		// else if (errno == ENOENT)
		// 	return_msg("Error: file not found\n", shell, 2);
		// else if (errno == EISDIR)
		// 	return_msg("Error: is a directory\n", shell, 126);
		// else if (errno == 	ENOSPC)
		// 	return_msg("Error: no space left on device\n", shell, 28);
		// else if (errno == EROFS)
		// 	return_msg("Error: read-only file system\n", shell, 30);
		// else
		// 	return_msg("Error: failed to open file\n", shell, 1);
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
		exit_partial("open faild", shell, 1);
	}
	return (fd);
}

char	*search_name(t_shell *shell)
{
	char	*filename;
	char	*num;

	while (1)
	{
		num = ft_itoa(shell->num_heredoc);
		if (!num)
			exit_all("Error: malloc failed\n", shell, 1);
		filename = ft_strjoin("heredoc_", num);
		if (!filename)
		{
			free(num);
			exit_all("Error: malloc failed\n", shell, 1);
		}
		free(num);
		shell->num_heredoc++;
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
	}
	return (filename);
}

int	process_heredoc_line(int fd, char *limiter, t_shell *shell)
{
	char	*line;

	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (g_exit_status == 130)
	{
		if (line)
			free(line);
		dup2(shell->original_stdin, 0);
		return (404);
	}
	if (!line)
	{
		ft_printf("merdeeee\n"); //strivere quello cgha fa bash con ctrl d
		return (0);
	}
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
		return (free(line), 0);
	ft_printfd(fd, "%s", line);
	free(line);
	return (1);
}

int	handle_heredoc(char *token, t_shell *shell)
{
	int			control;
	int			fd;
	char		*limiter;
	char		*filename;
	
	// struct sigaction	sa_old_int;
    // struct sigaction	sa_new_int;

    // // Save the current SIGINT handler
    // sigaction(SIGINT, NULL, &sa_old_int);
    
    // // Set up heredoc-specific SIGINT handler
    // sa_new_int.sa_handler = handle_ctrl_c_heredoc;
    // sigemptyset(&sa_new_int.sa_mask);
    // sa_new_int.sa_flags = 0;
    // sigaction(SIGINT, &sa_new_int, NULL);
	
	signal(SIGINT, handle_ctrl_c_heredoc);
	
	filename = search_name(shell);
	shell->heredocs = ft_realloc(shell->heredocs, (shell->num_heredoc + 1) * sizeof(char *), (shell->num_heredoc + 2) * sizeof(char *));
	if (!shell->heredocs)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->heredocs[shell->num_heredoc] = filename;
	shell->num_heredoc++;
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		//return_msg();
		exit_partial("open faild", shell, 1);
	limiter = ft_strjoin(token, "\n");
	if (!limiter)
		exit_all("Error: malloc failed\n", shell, 1);
	while (1)
	{
		control = process_heredoc_line(fd, limiter, shell);
		if (control == 404)
			return (control);
		else if (control == 0)
			break ;
	}
	free(limiter);
	close(fd);

	// // Restore the previous SIGINT handler
	// sigaction(SIGINT, &sa_old_int, NULL);   // Restore the previous SIGINT handler
	
	signal(SIGINT, handle_ctrl_c);

	fd = handle_fdin(filename, shell);
	return (fd);
}
