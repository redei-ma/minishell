/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:23:27 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/24 17:05:21 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_cmd_size(t_cmd *lst)
{
	t_cmd	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	is_empty(char *str)
{
	int	i;

	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	return (1);
}
