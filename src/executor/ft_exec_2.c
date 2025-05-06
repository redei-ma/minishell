/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:11:35 by redei-ma         #+#    #+#             */
/*   Updated: 2025/05/05 14:05:04 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*test_path(char **cmd_path, char *cmd, int j)
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

static char	*find_command_path(char *path, char *cmd)
{
	char	**cmd_path;
	char	*full_path;
	int		j;

	cmd_path = ft_split(path, ':');
	if (!cmd_path)
		exit_all("Error: malloc failed\n", NULL, 1);
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
