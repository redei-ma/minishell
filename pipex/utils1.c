/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 19:27:47 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/25 16:25:18 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*test_path(char **cmd_path, char *cmd, int j)
{
	int		i;
	char	*full_path;
	char	*tmp;

	i = 0;
	while (cmd_path[i])
	{
		tmp = ft_strjoin(cmd_path[i], "/");
		if (!tmp)
			return (ft_freemat((void **)cmd_path, j), NULL);
		full_path = ft_strjoin(tmp, cmd);
		if (!full_path)
			return (ft_freemat((void **)cmd_path, j), free(tmp), NULL);
		if (access(full_path, X_OK) == 0)
			return (ft_freemat((void **)cmd_path, j), free(tmp), full_path);
		free(tmp);
		free(full_path);
		i++;
	}
	return (NULL);
}

char	*find_command_path(char *path, char *cmd)
{
	char	**cmd_path;
	char	*full_path;
	int		j;

	cmd_path = ft_split(path, ':');
	if (!cmd_path)
		return (NULL);
	j = 0;
	while (cmd_path[j])
		j++;
	full_path = test_path(cmd_path, cmd, j);
	if (full_path)
		return (full_path);
	ft_freemat((void **)cmd_path, j);
	return (NULL);
}

char	*get_path(char *cmd, char **envp)
{
	int		i;
	char	*cmd_path;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			cmd_path = find_command_path(envp[i] + 5, cmd);
			if (!cmd_path)
				return (NULL);
			return (cmd_path);
		}
		i++;
	}
	return (NULL);
}

void	set_pipe(t_pipex **piper)
{
	(*piper)->i = 0;
	(*piper)->fds = malloc((*piper)->n_pipes * sizeof(int *));
	if (!(*piper)->fds)
		exit_error("malloc failed", piper, NULL, NULL);
	while ((*piper)->i < (*piper)->n_pipes)
	{
		(*piper)->fds[(*piper)->i] = malloc(2 * sizeof(int));
		if (!(*piper)->fds[(*piper)->i])
			exit_error("malloc failed", piper, NULL, NULL);
		if (pipe((*piper)->fds[(*piper)->i]) == -1)
			exit_error("pipe failed", piper, NULL, NULL);
		(*piper)->i++;
	}
}

void	set_piper(t_pipex **piper, int ac, char **av, char **envp)
{
	(*piper)->ac = ac;
	(*piper)->av = av;
	(*piper)->envp = envp;
	(*piper)->n_cmds = ac - 3;
	(*piper)->n_pipes = ac - 4;
	(*piper)->pids = ft_calloc((*piper)->n_cmds, sizeof(pid_t));
	if (!(*piper)->pids)
		exit_error("malloc failed", piper, NULL, NULL);
	set_pipe(piper);
	(*piper)->flag = 0;
}
