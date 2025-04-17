/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 08:11:35 by renato            #+#    #+#             */
/*   Updated: 2025/04/02 18:06:40 by redei-ma         ###   ########.fr       */
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
