/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by renato            #+#    #+#             */
/*   Updated: 2025/04/17 14:52:21 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **args)
{
	int	exit_code;

	exit_code = 0;
	if (args && args[0])
	{
		if (args[1])
			return_partial("exit: too many arguments", shell, 36);
		else if (ft_natoi(args[0]) == 0
			&& (args[0][0] != 0 || args[0][0] != '\0'))
			return_partial("exit: numeric argument required", shell, 44);
		else
			exit_code = ft_natoi(args[0]) % 256;
	}
	ft_printfd(1, "exit\n");
	exit_all(NULL, shell, exit_code);
}

void	ft_env(t_shell *shell)
{
	int	i;

	if (shell->cmds->args)
		return_partial("env: bad arguments", shell, 1);
	else
	{
		i = 0;
		while (shell->env[i])
		{
			if (find_eq_sn(shell->env[i]) != -1)
				ft_printfd_shell(shell, "%s\n", shell->env[i]);
			i++;
		}
		shell->exit_status = 0;
	}
}

void	ft_unset(t_shell *shell, char **args)
{
	int	index;
	int	i;
	int	j;

	if (!args[0])
		return_partial("unset: too few arguments", shell, 1);
	i = 0;
	while (args[i])
	{
		index = srcd_env(shell, args[i]);
		if (index != -1)
		{
			free(shell->env[index]);
			j = index;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->env[j] = NULL;
			shell->max--;
		}
		i++;
	}
	shell->exit_status = 0;
}

void	ft_pwd(t_shell *shell)
{
	char	*cwd;

	if (shell->cmds && shell->cmds->args && shell->cmds->args[0])
	{
		return_partial("pwd: too many arguments", shell, 1);
		return ;
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return_partial("pwd: error retrieving current directory", shell, 1);
	ft_printfd_shell(shell, "%s\n", cwd);
	free(cwd);
	shell->exit_status = 0;
}
