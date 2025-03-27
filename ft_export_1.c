/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/03/27 19:07:31 by redei-ma         ###   ########.fr       */
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
	char		**srtd_env;

	srtd_env = malloc(sizeof(char *) * (shell->max + 2));
	if (!srtd_env)
	{
		free(srtd_env);
		return ;
	}
	i = -1;
	while (++i < shell->max)
		srtd_env[i] = shell->env[i];
	srtd_env[i] = NULL;
	sort_env(srtd_env);
	i = -1;
	while (srtd_env[++i])
		ft_printfd_shell(shell, "declare -x %s\n", (char *)srtd_env[i]);
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
