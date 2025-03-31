/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:04:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/31 21:12:55 by renato           ###   ########.fr       */
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
		signal(SIGINT, handle_ctrl_c_exec);
		ft_exec(shell);
	}
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
			exit_all(NULL, shell, 0);
		}
		shell->cmds = shell->cmds->next;
		i++;
	}
	shell->piper->n_pids = i;
	close_all(shell);
	while (wait(NULL) > 0)
		;
	signal(SIGINT, handle_ctrl_c);
	if (WIFEXITED(status))
		g_exit_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		g_exit_status = 128 + WTERMSIG(status);
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
		signal(SIGINT, handle_ctrl_c_exec);
		pid = fork();
		if (pid == -1)
			exit_all("Error: fork failed\n", shell, 1);
		else if (pid == 0)
			ft_exec(shell);
		wait(NULL);
		signal(SIGINT, handle_ctrl_c);
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_exit_status = 128 + WTERMSIG(status);
	}
}

void	cmd_manage(t_shell *shell)
{
	int	num_cmd;

	num_cmd = ft_cmd_size(shell->cmds);
	if (num_cmd > 1)
		fork_manger(shell);
	else
		cmd_find_dad(shell, shell->cmds->cmd);
	return_partial(NULL, shell, 0);
}
