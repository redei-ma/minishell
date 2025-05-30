/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 17:17:40 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **args)
{
	if (ft_cmd_size(shell->head) == 1)
		ft_printfd(1, "exit\n");
	if (args && args[0])
	{
		if (ft_natoi(args[0]) == 0
			&& !(args[0][0] == 0 && args[0][1] == '\0'))
			exit_all("exit: numeric argument required", shell, 2);
		else if (args[1])
		{
			ft_printfd(2, "exit: too many arguments\n");
			shell->exit_status = 1;
			return ;
		}
		else
			shell->exit_status = ft_natoi(args[0]) % 256;
	}
	exit_all(NULL, shell, shell->exit_status);
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

static void	process_unset_arg(t_shell *shell, char *arg, int *stat)
{
	int	index;
	int	j;

	if (!is_valid_identifier(arg))
	{
		ft_printfd(2, "unset: '%s' not a valide identifier\n", arg);
		*stat = 1;
		return ;
	}
	index = srcd_env(shell, arg);
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
}

void	ft_unset(t_shell *shell, char **args)
{
	int	i;
	int	stat;

	stat = 0;
	if (!args || !args[0])
	{
		return_partial("unset: too few arguments", shell, 1);
		return ;
	}
	i = 0;
	while (args[i])
	{
		process_unset_arg(shell, args[i], &stat);
		i++;
	}
	if (stat)
		shell->exit_status = 1;
	else
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
