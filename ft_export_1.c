/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/01 17:46:12 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_eq_sn(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	sort_env(char **srtd_env)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (srtd_env[i])
	{
		j = i + 1;
		while (srtd_env[j])
		{
			if (ft_strcmp(srtd_env[i], srtd_env[j]) > 0)
			{
				tmp = srtd_env[i];
				srtd_env[i] = srtd_env[j];
				srtd_env[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_declare(t_shell *shell)
{
	int			i;
	int			j;
	char		**srtd_env;

	i = -1;
	srtd_env = copy_mat(shell->env, NULL, shell);
	if (!srtd_env)
		exit_all("Error: malloc failed\n", shell, 1);
	sort_env(srtd_env);
	while (srtd_env[++i])
	{
		write_to_fd(shell, "declare -x ", 11);
		j = 0;
		while (srtd_env[i][j])
		{
			write_to_fd(shell, srtd_env[i] + j, 1);
			if (srtd_env[i][j] == '=')
				write_to_fd(shell, "\"", 1);
			j++;
		}
		write_to_fd(shell, "\"\n", 2);
	}
	free(srtd_env);
}

void	process_export_arg(t_shell *shell, char *arg)
{
	int		eqp;
	char	*name;
	char	*val;

	eqp = find_eq_sn(arg);
	if (eqp != -1)
	{
		val = NULL;
		name = ft_substr(arg, 0, eqp);
		if (name)
			val = ft_substr(arg, eqp + 1, ft_strlen(arg) - eqp - 1);
		if (!name || !val)
		{
			free(name);
			free(val);
			return ;
		}
		upd_var(shell, name, val);
		free(name);
		free(val);
	}
	else if (srcd_env(shell, arg) == -1)
	{
		upd_var(shell, arg, "");
	}
}

void	ft_export(t_shell *shell, char **args)
{
	int	i;

	if (!args)
	{
		print_env_declare(shell);
		return ;
	}
	i = 0;
	while (args[i])
	{
		process_export_arg(shell, args[i]);
		i++;
	}
}
