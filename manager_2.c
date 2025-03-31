/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by renato            #+#    #+#             */
/*   Updated: 2025/03/31 21:39:27 by renato           ###   ########.fr       */
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
			shell->max--;
		}
		i++;
	}
	g_exit_status = 0;
}

void	ft_pwd(t_shell *shell)
{
	char	cwd[4096];

	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printfd_shell(shell, "%s\n", cwd);
	else
		ft_printfd(2, "pwd: error retrieving current directory: getcwd: %s\n", strerror(errno));
	g_exit_status = 0;
}

void	ft_cd(char **string, t_shell *shell)
{
	if (!string)
		return_partial("cd: too few arguments", shell, 1);
	else if (ft_matlen(string) != 1)
		return_partial("cd: too many arguments", shell, 1);
	else if (ft_strlen(string[0]) == 0)
		return_partial("cd: string not in pwd: ", shell, 1);
	else if (chdir(string[0]) != 0)
		return_partial("cd: no such file or directory: ", shell, 1);
	// capire se devo chiudere gli fd o no
	// close_all(shell);
	// return_partial(NULL, shell, 0); //capire se va messo anche negli altri
	g_exit_status = 0;
}
