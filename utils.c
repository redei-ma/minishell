/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:23:27 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/02 17:21:30 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_space(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

char	**copy_mat(char **mat, int *max_env, t_shell *shell)
{
	int		i;
	char	**new_mat;

	i = 0;
	while (mat[i])
		i++;
	new_mat = ft_calloc((i + 1), sizeof(char *));
	if (!new_mat)
		exit_all("Error: malloc failed\n", shell, 1);
	i = 0;
	while (mat[i])
	{
		new_mat[i] = ft_strdup(mat[i]);
		if (!new_mat[i])
			exit_all("Error: malloc failed\n", shell, 1);
		i++;
	}
	if (max_env)
		*max_env = i;
	return (new_mat);
}

void	ft_printfd_shell(t_shell *shell, const char *format, char *args)
{
	int	fd;

	if (shell->cmds->file_a == -1 && shell->cmds->file_o == -1)
		fd = 1;
	else if (shell->cmds->file_a != -1)
		fd = shell->cmds->file_a;
	else
		fd = shell->cmds->file_o;
	ft_printfd(fd, format, args);
}

int	is_env(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if (cmd[i] && cmd[i] == '=' && i > 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(cmd, "cd", 2) == 0)
		return (1);
	else if (ft_strncmp(cmd, "pwd", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "export", 6) == 0)
		return (1);
	else if (ft_strncmp(cmd, "unset", 5) == 0)
		return (1);
	else if (ft_strncmp(cmd, "env", 3) == 0)
		return (1);
	else if (ft_strncmp(cmd, "exit", 4) == 0)
		return (1);
	return (0);
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
