/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/22 12:35:42 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*already_path(char *cmd)
{
	char	*path;

	path = ft_strdup(cmd);
	if (!path)
		return (NULL);
	if (access(cmd, F_OK) == 0)
		return (path);
	free(path);
	return (NULL);
}

char	**ft_cmd_join(char *cmd, char **args, t_shell *shell)
{
	char	**command;
	int		i;

	i = ft_matlen(args);
	command = ft_calloc((i + 2), sizeof(char *));
	if (!command)
		exit_all("Error: malloc failed\n", shell, 1);
	command[0] = ft_strdup(cmd);
	if (!command[0])
	{
		free(command);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	i = 0;
	while (args && args[i])
	{
		command[i + 1] = ft_strdup(args[i]);
		if (!command[i + 1])
		{
			ft_free_char_mat(command);
			exit_all("Error: malloc failed\n", shell, 1);
		}
		i++;
	}
	return (command);
}

void	set_dups(t_cmd *cmd)
{
	if (cmd->file_i != -1)
	{
		if (dup2(cmd->file_i, STDIN_FILENO) == -1)
			exit_all("dup2 input", shell, 1);
	}
	if (cmd->file_a != -1)
	{
		if (dup2(cmd->file_a, STDOUT_FILENO) == -1)
			exit_all("dup2 append", shell, 1);
	}
	else if (cmd->file_o != -1)
	{
		if (dup2(cmd->file_o, STDOUT_FILENO) == -1)
			exit_all("dup2 output", shell, 1);
	}
}

void	ft_exec(t_shell *shell)
{
	char		*full_path;
	char		**command;

	if (shell->cmds->cmd[0] == '/')
		full_path = already_path(shell->cmds->cmd);
	else if (shell->cmds->cmd[0] == '.' && shell->cmds->cmd[1] == '/')
		full_path = already_path(shell->cmds->cmd);
	else
		full_path = get_path(shell->cmds->cmd, shell->env);
	if (!full_path)
		exit_partial("Error: command not found", shell, 127); //da gestire msg
	command = ft_cmd_join(shell->cmds->cmd, shell->cmds->args, shell);
	if (!command)
		exit_all("Error: malloc failed\n", shell, 1);
	set_dups(shell->cmds);
	close_all(shell);
	delete_heredoc(shell);
	free_all(shell);
	execve(full_path, command, shell->env);
	free(full_path);
	ft_free_char_mat(command);
	ft_printfd(2, "Error: execve failed\n");
	exit(127);
}
