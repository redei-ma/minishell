/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 00:04:33 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:59:21 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_find_son(t_shell *shell, char *cmd)
{
	if (!cmd)
	{
		shell->exit_status = 127;
		return ;
	}
	if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		return ;
	else
	{
		signal(SIGINT, handle_ctrl_c_exec);
		ft_exec(shell);
	}
	exit_all(NULL, shell, shell->exit_status);
}

static void	forking(t_shell *shell, int i)
{
	shell->piper->pids[i] = fork();
	if (shell->piper->pids[i] == -1)
		exit_all("Error: fork failed\n", shell, 1);
	else if (shell->piper->pids[i] == 0)
		cmd_find_son(shell, shell->cmds->cmd);
}

static void	fork_manger(t_shell *shell)
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
	shell->exit_status = ft_wifexit();
}

void	cmd_manage(t_shell *shell)
{
	int	num_cmd;

	num_cmd = ft_cmd_size(shell->cmds);
	if (num_cmd > 1)
		fork_manger(shell);
	else
		cmd_find_dad(shell, shell->cmds->cmd);
	return_partial(NULL, shell, shell->exit_status);
}
