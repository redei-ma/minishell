/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by renato            #+#    #+#             */
/*   Updated: 2025/04/03 18:15:03 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **args)
{
	int	exit_code;
	int	len;

	exit_code = 0;
	len = ft_matlen(args);
	if (args && args[0])
	{
		if (len > 1)
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

	i = 0;
	while (shell->env[i])
	{
		if (find_eq_sn(shell->env[i]) != -1)
			ft_printfd_shell(shell, "%s\n", shell->env[i]);
		i++;
	}
	g_exit_status = 0;
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

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return_partial("pwd: error retrieving current directory", shell, 1);
	ft_printfd_shell(shell, "%s\n", cwd);
	free(cwd);
	g_exit_status = 0;
}

void	ft_cd(char **string, t_shell *shell)
{
	if (!string || ft_matlen(string) != 1)
		return_partial("cd: bad arguments", shell, 1);
	else if (chdir(string[0]) != 0)
		return_partial("cd: no such file or directory", shell, 1);
	// capire se devo chiudere gli fd o no
	// close_all(shell);
	// return_partial(NULL, shell, 0); //capire se va messo anche negli altri
	g_exit_status = 0;
}
