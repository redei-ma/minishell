/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/29 11:36:28 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	new_pwd(t_shell *shell)
{
	char	*oldpwd_var;
	char	*export_args[2];
	char	*cwd;

	cwd = getcwd(NULL, 0);
	oldpwd_var = ft_strjoin("PWD=", cwd);
	if (!oldpwd_var)
	{
		free(cwd);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	export_args[0] = oldpwd_var;
	export_args[1] = NULL;
	ft_export(shell, export_args);
	free(oldpwd_var);
}

void	new_old_pwd(char *cwd, t_shell *shell)
{
	char	*oldpwd_var;
	char	*export_args[2];

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
		free(cwd);
		if (errno == EACCES)
			return_partial("cd: permission denied", shell, 1);
		else if (errno == ENOENT)
			return_partial("cd: no such file or directory", shell, 1);
		else if (errno == ENOTDIR)
			return_partial("cd: not a directory", shell, 1);
		else
			return_partial("cd: unknown error", shell, 1);
		return ;
	}
	if (cwd)
	{
		new_old_pwd(cwd, shell);
		new_pwd(shell);
	}
	free(cwd);
	status = 0;
}
