/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 16:46:11 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	new_pwd(t_shell *shell)
{
	char	*pwd_var;
	char	*export_args[2];
	char	*cwd;

	if (srcd_env(shell, "PWD") == -1)
		return ;
	cwd = getcwd(NULL, 0);
	pwd_var = ft_strjoin("PWD=", cwd);
	if (!pwd_var)
	{
		free(cwd);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	export_args[0] = pwd_var;
	export_args[1] = NULL;
	ft_export(shell, export_args);
	free(pwd_var);
	free(cwd);
}

static void	new_old_pwd(char *cwd, t_shell *shell)
{
	char	*oldpwd_var;
	char	*export_args[2];

	export_args[1] = NULL;
	if (srcd_env(shell, "OLDPWD") == -1)
		return ;
	else if (srcd_env(shell, "PWD") == -1)
	{
		export_args[0] = "OLDPWD";
		ft_unset(shell, export_args);
		ft_export(shell, export_args);
		return ;
	}
	oldpwd_var = ft_strjoin("OLDPWD=", cwd);
	if (!oldpwd_var)
	{
		free(cwd);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	export_args[0] = oldpwd_var;
	ft_export(shell, export_args);
	free(oldpwd_var);
}

static void	handle_cd_error(char *cwd, t_shell *shell)
{
	free(cwd);
	if (errno == EACCES)
		return_partial("cd: permission denied", shell, 1);
	else if (errno == ENOENT)
		return_partial("cd: no such file or directory", shell, 1);
	else if (errno == ENOTDIR)
		return_partial("cd: not a directory", shell, 1);
	else
		return_partial("cd: unknown error", shell, 1);
}

void	ft_cd(char **string, t_shell *shell)
{
	char	*cwd;

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
		handle_cd_error(cwd, shell);
		return ;
	}
	if (cwd)
	{
		new_old_pwd(cwd, shell);
		free(cwd);
		new_pwd(shell);
	}
	shell->exit_status = 0;
}
