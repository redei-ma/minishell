/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:44:34 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/16 13:45:05 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_cd(char **string, t_shell *shell)
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
