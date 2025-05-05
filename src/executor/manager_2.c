/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:02:16 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:52:52 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_exec_dad(t_shell *shell)
{
	pid_t	pid;

	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, handle_ctrl_bl_exec);
	pid = fork();
	if (pid == -1)
		exit_all("Error: fork failed\n", shell, 1);
	else if (pid == 0)
	{
		signal(SIGINT, handle_ctrl_c_exec);
		ft_exec(shell);
	}
	shell->exit_status = ft_wifexit();
	signal(SIGQUIT, handle_ctrl_bl);
	signal(SIGINT, handle_ctrl_c);
}

void	cmd_find_dad(t_shell *shell, char *cmd)
{
	if (!cmd || shell->cmds->skip)
	{
		if (shell->cmds->skip)
			shell->exit_status = 1;
		return ;
	}
	else if (is_builtin(cmd))
		exe_builtin(shell);
	else if (is_env(cmd))
		return ;
	else
		cmd_exec_dad(shell);
}
