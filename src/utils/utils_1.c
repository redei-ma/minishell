/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:23:27 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/05 17:27:18 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	exe_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->cmds->cmd, "echo", 4) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->cmds->cmd, "cd", 2) == 0)
		ft_cd((shell)->cmds->args, shell);
	else if (ft_strncmp(shell->cmds->cmd, "pwd", 3) == 0)
		ft_pwd(shell);
	else if (ft_strncmp(shell->cmds->cmd, "export", 6) == 0)
		ft_export(shell, shell->cmds->args);
	else if (ft_strncmp(shell->cmds->cmd, "unset", 5) == 0)
		ft_unset(shell, shell->cmds->args);
	else if (ft_strncmp(shell->cmds->cmd, "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->cmds->cmd, "exit", 4) == 0)
		ft_exit(shell, shell->cmds->args);
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

int	is_empty(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->input[i] && ft_isspace(shell->input[i]))
		i++;
	if (shell->input[i])
		return (0);
	return_partial(NULL, shell, shell->exit_status);
	return (1);
}
