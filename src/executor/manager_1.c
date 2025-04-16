/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:04:33 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 13:43:54 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_find_son(t_shell *shell, char *cmd)
{
	if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		return ;
	else
	{
		signal(SIGINT, handle_ctrl_c_exec);
		ft_exec(shell);
	}
	exit_all(NULL, shell, 0);
}

void	forking(t_shell *shell, int i)
{
	shell->piper->pids[i] = fork();
	if (shell->piper->pids[i] == -1)
		exit_all("Error: fork failed\n", shell, 1);
	else if (shell->piper->pids[i] == 0)
		cmd_find_son(shell, shell->cmds->cmd);
}

void	fork_manger(t_shell *shell)
{
	int	i;

	i = shell->piper->n_pids;
	while (shell->cmds)
	{
		if (shell->cmds->skip)
		{
			shell->cmds = shell->cmds->next;
			continue ;
		}
		shell->piper->pids = ft_realloc(shell->piper->pids,
				(i + 1) * sizeof(pid_t), (i + 2) * sizeof(pid_t));
		if (!shell->piper->pids)
			exit_all("Error: malloc failed\n", shell, 1);
		forking(shell, i);
		shell->cmds = shell->cmds->next;
		i++;
	}
	shell->piper->n_pids = i;
	close_all(shell);
	signal(SIGINT, handle_ctrl_c);
	g_exit_status = ft_wifexit();
}

void	cmd_find_dad(t_shell *shell, char *cmd)
{
	pid_t	pid;

	if (shell->cmds->skip)
	{
		g_exit_status = 1;
		return ;
	}
	else if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		return ;
	else
	{
		signal(SIGINT, handle_ctrl_c_exec);
		pid = fork();
		if (pid == -1)
			exit_all("Error: fork failed\n", shell, 1);
		else if (pid == 0)
			ft_exec(shell);
		signal(SIGINT, handle_ctrl_c);
		g_exit_status = ft_wifexit(pid);
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
	return_partial(NULL, shell, g_exit_status);
}
