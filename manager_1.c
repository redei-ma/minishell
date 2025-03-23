/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:04:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/23 01:58:01 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cmd_find_son(t_shell *shell, char *cmd)
{
	if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		ft_export(shell, shell->cmds->args);
	else
	{
		ft_exec(shell);
		exit_error(NULL, shell, 127); //che messaggio va stampato? o lo fa gia subito dopo execve?
	}
}

void	fork_manger(t_shell *shell)
{
	int i;

	i = 1;
	while (shell->cmds)
	{
		shell->piper->pids = ft_realloc(shell->piper->pids, (i - 1) * sizeof(pid_t), i * sizeof(pid_t));
		if (!shell->piper->pids)
			exit_error("Error: malloc failed\n", shell, 1);
		shell->piper->pids[i - 1] = fork();
		if (shell->piper->pids[i - 1] == -1)
			exit(1); // exit_error da gestire
		else if (shell->piper->pids[i - 1] == 0)
		{
			cmd_find_son(shell, shell->cmds->cmd);
			//chiusura tutto per figlio
			exit_error(NULL, shell, 1); //che messaggio va stampato? o lo fa gia subito dopo execve?
		}
		shell->cmds = shell->cmds->next;
		i++;
	}
	while (wait(NULL) > 0)
		;
}

void	cmd_find_dad(t_shell *shell, char *cmd)
{
	if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		ft_export(shell, &shell->cmds->cmd);
	else
	{
		shell->piper->pids = ft_realloc(shell->piper->pids, 0, 1 * sizeof(pid_t));
		if (!shell->piper->pids)
			exit_error("Error: malloc failed\n", shell, 1);
		shell->piper->pids[0] = fork();
		if (shell->piper->pids[0] == -1)
			exit(1); // exit_error da gestire
		else if (shell->piper->pids[0] == 0)
		{
			ft_exec(shell);
			exit_error(NULL, shell, 127); //che messaggio va stampato? o lo fa gia subito dopo execve?
		}
		wait(NULL);
		//bisogna cercare lo stato di uscita del figlio e aggiornarlo
	}
}

void	cmd_manage(t_shell *shell)
{
	int	num_cmd;

	num_cmd = ft_cmd_size(shell->cmds);
	//se num_cmd == 0, cosa succede? in teroria non dovrebbe succedere perche ne creo subito uno
	if (num_cmd == 1)
		cmd_find_dad(shell, shell->cmds->cmd);
	else if (num_cmd > 1)
		fork_manger(shell);
	//chiusura tutto per padre
}
