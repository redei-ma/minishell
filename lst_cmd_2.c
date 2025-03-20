/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:09 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 22:24:50 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_fdout(char *token, char c)
{
	int	fd;

	fd = -1;
	if (c == 'o')
		fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'a')
		fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		//exit_error();
		exit(1);
	}
	return (fd);
}

int	handle_fdin(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
	{
		//exit_error(); devo settare bene erno per file non esistente
		exit(1);
	}
	return (fd);
}

char	*search_name(void)
{
	int		n;
	char	*num;
	char	*filename;

	n = 0;
	while (1)
	{
		num = ft_itoa(n);
		if (!num)
			//exit_error();
			exit(1);
		filename = ft_strjoin("heredoc_", ft_itoa(n));
		free(num);
		if (!filename)
			//exit_error();
			exit(1);
		if (access(filename, F_OK) == -1)
			break ;
		free(filename);
		n++;
	}
	return (filename);
}

int process_heredoc_line(int fd, char *limiter)
{
	char *line;
	
	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (!line)
		return (0);
	if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0)
	{
		free(line);
		return (0);
	}
	ft_printfd(fd, "%s", line);
	free(line);
	return (1);
}

int	handle_heredoc(char *token)
{
	int		fd;
	char	*limiter;
	char	*filename;

	filename = search_name();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		//exit_error();
		exit(1);
	limiter = ft_strjoin(token, "\n");
	if (!limiter)
		//exit_error();
		exit(1);
	while (process_heredoc_line(fd, limiter))
		;
	free(limiter);
	close(fd);
	fd = handle_fdin(filename);
	free(filename);
	return (fd);
}
