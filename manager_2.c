/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manager_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:12:52 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 12:46:03 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_exit(t_shell *shell, char **args)
{
	int	exit_code = 0;

	if (!shell)
		return ;
	write(1, "exit\n", 5);
	if (args[0])
	{
		if (args[1])
		{
			write(2, "exit: too many arguments\n", 36);
			return ;
		}
		else if (ft_natoi(args[0]) == 0 && (args[0][0] != 0 || args[0][0] != '\0'))
		{
			write(2, "exit: numeric argument required\n", 44);
			//exit_code = 255;
		}
		else
			exit_code = ft_natoi(args[0]) % 256;
	}
	//free_shell(shell);
	exit(exit_code);
}

void	ft_env(t_shell *shell)
{
	int	i;

	i = 0;
	if (!shell)
		exit(1);
	while (shell->env[i])
	{
		if (find_eq_sn(shell->env[i]) != -1)
			ft_printf("%s\n", shell->env[i]);
		i++;
	}
}

void	ft_unset(t_shell *shell, char **args)
{
	int	index;
	int	i;
	int	j;

	if (!args[0])
		exit(1);
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
}

void	ft_pwd()
{
	char	cwd[4096];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("pwd");
		exit(1);
	}
}
