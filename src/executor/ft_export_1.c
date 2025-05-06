/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:51:52 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_env_var(t_shell *shell, char *var)
{
	int	j;
	int	iseq;

	j = 0;
	iseq = 0;
	while (var[j] != '\0')
	{
		write_to_fd(shell, &var[j], 1);
		if (var[j] == '=')
		{
			iseq = 1;
			write_to_fd(shell, "\"", 1);
		}
		j++;
	}
	if (iseq)
		write_to_fd(shell, "\"\n", 2);
	else
		write_to_fd(shell, "\n", 1);
}

static void	sort_env(char **srtd_env)
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

static void	print_env_declare(t_shell *shell)
{
	int		i;
	char	**srtd_env;

	i = -1;
	srtd_env = copy_mat(shell->env, NULL, shell);
	if (!srtd_env)
		exit_all("Error: malloc failed\n", shell, 1);
	sort_env(srtd_env);
	while (srtd_env[++i])
	{
		write_to_fd(shell, "declare -x ", 11);
		print_env_var(shell, srtd_env[i]);
	}
	ft_free_char_mat(srtd_env);
}

void	ft_export(t_shell *shell, char **args)
{
	int	i;

	if (!args)
	{
		print_env_declare(shell);
		shell->exit_status = 0;
	}
	else
	{
		i = 0;
		while (args[i])
		{
			process_export_arg(shell, args[i]);
			i++;
		}
	}
}
