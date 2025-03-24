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

void ft_exec(t_shell *shell)
{
	t_cmd *cmd;
	char *full_path;
	char **command;

	cmd = shell->cmds;
	if (cmd->cmd[0] == '/')
		full_path = already_path(cmd->cmd);
	else
		full_path = get_path(cmd->cmd, shell->env);
	if (!full_path)
		exit_partial("Error: command not found", shell, 127); //da gestire msg
	if (cmd->file_i != -1)
	{
		if (dup2(cmd->file_i, STDIN_FILENO) == -1)
			exit_all("dup2 input", shell, 1);
		// safe_close(cmd->file_i);
	}
	if (cmd->file_a != -1)
	{
		if (dup2(cmd->file_a, STDOUT_FILENO) == -1)
			exit_all("dup2 append", shell, 1);
		// safe_close(cmd->file_a);
	}
	else if (cmd->file_o != -1)
	{
		if (dup2(cmd->file_o, STDOUT_FILENO) == -1)
			exit_all("dup2 output", shell, 1);
		// safe_close(cmd->file_o);
	}
	command = ft_cmd_join(cmd->cmd, cmd->args, shell);
	if (!command)
		exit_all("Error: malloc failed\n", shell, 1);
	// devo liberare la struttura del figlio? in pipex non mi pare lo facciano
	close_all(shell);
	// delete_heredoc(shell);
	// free_all(shell);
	execve(full_path, command, shell->env);
	free(full_path);
	ft_free_char_mat(command);
	ft_printfd(2, "Error: execve failed\n");
	exit(127);
}
