/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/17 17:59:07 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exe_builtin(t_shell *shell)
{
	if (ft_strcmp(shell->cmds->cmd, "echo") == 0)
		ft_echo(shell);
	else if (ft_strcmp(shell->cmds->cmd, "cd") == 0)
		ft_cd((shell)->cmds->args, shell);
	else if (ft_strcmp(shell->cmds->cmd, "pwd") == 0)
		ft_pwd(shell);
	else if (ft_strcmp(shell->cmds->cmd, "export") == 0)
		ft_export(shell, shell->cmds->args);
	else if (ft_strcmp(shell->cmds->cmd, "unset") == 0)
		ft_unset(shell, shell->cmds->args);
	else if (ft_strcmp(shell->cmds->cmd, "env") == 0)
		ft_env(shell);
	else if (ft_strcmp(shell->cmds->cmd, "exit") == 0)
		ft_exit(shell, shell->cmds->args);
}

int	ft_wifexit(void)
{
	int	status;

	status = 0;
	while (wait(NULL) > 0)
		;
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (0);
}
