/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:51:12 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:15:20 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(char ***args, char *token, t_shell *shell)
{
	int	count;

	if (!(*args))
	{
		*args = (char **)ft_calloc(2, sizeof(char *));
		if (!*args)
			exit_all("Error: malloc failed\n", shell, 1);
		(*args)[0] = ft_strdup(token);
		if (!(*args)[0])
			exit_all("Error: malloc failed\n", shell, 1);
	}
	else
	{
		count = 0;
		while ((*args)[count])
			count++;
		*args = ft_realloc(*args, (count + 1) * sizeof(char *),
				(count + 2) * sizeof(char *));
		if (!*args)
			exit_all("Error: malloc failed\n", shell, 1);
		(*args)[count] = ft_strdup(token);
		if (!(*args)[count])
			exit_all("Error: malloc failed\n", shell, 1);
	}
}

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
		shell->cmds->skip = 1;
		ft_printfd(2, "minishell: %s: No such file or directory\n", token);
	}
	return (fd);
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
