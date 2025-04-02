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

void	set_dups(t_cmd *cmd, t_shell *shell)
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
	char		**copy_env;

	full_path = get_path(shell->cmds->cmd, shell->env);
	if (!full_path)
	{
		full_path = ft_strdup(shell->cmds->cmd);
		if (!full_path)
			exit_all("Error: malloc failed\n", shell, 1); //non sarebbe proprio cosi
	}
	command = ft_cmd_join(shell->cmds->cmd, shell->cmds->args, shell);
	if (!command)
	{
		free(full_path);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	set_dups(shell->cmds, shell);
	// se fallisce non frea cio che ho rcreato qui
	copy_env = copy_mat(shell->env, NULL, shell);
	//se non  torna mi perdo cose da freaer qua
	close_all(shell);
	free_all(shell);
	execve(full_path, command, copy_env);
	free(full_path);
	ft_free_char_mat(command);
	ft_free_char_mat(copy_env);
	ft_printfd(2, "Error: command not found\n");
	exit(127);
}
