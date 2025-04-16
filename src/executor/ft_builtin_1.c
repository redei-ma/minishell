/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:03:53 by renato           ###   ########.fr       */
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
		g_exit_status = 0;
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
	g_exit_status = 0;
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
	g_exit_status = 0;
}

void ft_cd(char **string, t_shell *shell)
{
	char	*cwd;
	char	*oldpwd_var;
	char	*export_args[2];

	cwd = getcwd(NULL, 0);
	if (!cwd)
		ft_printfd(2, "cd: error getting current directory\n");
	if (!string || ft_matlen(string) != 1)
	{
		free(cwd);
		return_partial("cd: bad arguments", shell, 1);
		return ;
	}
	if (chdir(string[0]) != 0)
	{
		free(cwd);
		return_partial("cd: no such file or directory", shell, 1);
		return ;
	}
	if (cwd)
	{
		oldpwd_var = ft_strjoin("OLDPWD=", cwd);
		if (!oldpwd_var)
		{
			free(cwd);
			exit_all("Error: malloc failed\n", shell, 1);
		}
		export_args[0] = oldpwd_var;
		export_args[1] = NULL;
		ft_export(shell, export_args);
		free(oldpwd_var);
		free(cwd);
	}
	g_exit_status = 0;
}
