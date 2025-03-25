/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:04:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/24 19:32:53 by redei-ma         ###   ########.fr       */
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
		ft_exec(shell);
}

void	fork_manger(t_shell *shell)
{
	int	i;

	i = shell->piper->n_pids;
	while (shell->cmds)
	{
		shell->piper->pids = ft_realloc(shell->piper->pids,
			(i + 1) * sizeof(pid_t), (i + 2) * sizeof(pid_t));
		if (!shell->piper->pids)
			exit_all("Error: malloc failed\n", shell, 1);
		shell->piper->pids[i] = fork();
		if (shell->piper->pids[i] == -1)
			exit_all("Error: fork failed\n", shell, 1);
		else if (shell->piper->pids[i] == 0)
		{
			cmd_find_son(shell, shell->cmds->cmd);
			exit(0);
			// exit_partial(NULL, shell, 0);
		}
		shell->cmds = shell->cmds->next;
		i++;
	}
	shell->piper->n_pids = i;
	close_all(shell);
	// ft_printfd(2, "All children have exited\n");
	while (wait(NULL) > 0)
		;
	// ft_printfd(2, "While finish\n");
	//controllare uscita figlio
}

void	cmd_find_dad(t_shell *shell, char *cmd)
{
	pid_t	pid;

	if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		ft_export(shell, &shell->cmds->cmd);
	else
	{
		pid = fork();
		if (pid == -1)
			exit_all("Error: fork failed\n", shell, 1);
		else if (pid == 0)
			ft_exec(shell);
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
	//return_partial(NULL, shell, 0);
	//chiusura tutto per padre
}
