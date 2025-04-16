/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:22:33 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_env_var(t_shell *shell, char *var)
{
	int	j;
	int	iseq;

	j = 0;
	iseq = 0;
	while (var[j])
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

void	print_env_declare(t_shell *shell)
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

int	handle_export_value(t_shell *shell, char *arg, int eq_pos)
{
	char	*name;
	char	*value;

	name = ft_substr(arg, 0, eq_pos);
	if (!name)
		return (0);
	value = ft_substr(arg, eq_pos + 1, ft_strlen(arg) - eq_pos - 1);
	if (!value)
	{
		free(name);
		return (0);
	}
	upd_var(shell, name, value, eq_pos);
	free(name);
	free(value);
	return (1);
}

void	process_export_arg(t_shell *shell, char *arg)
{
	int	eq_pos;

	if (arg[0] == '=')
	{
		ft_printfd(2, "export: `%s': not a valid identifier\n", arg);
		return ;
	}
	eq_pos = find_eq_sn(arg);
	if (eq_pos != -1)
		handle_export_value(shell, arg, eq_pos);
	else if (srcd_env(shell, arg) == -1)
		upd_var(shell, arg, "", eq_pos);
}

void	ft_export(t_shell *shell, char **args)
{
	int	i;

	if (!args)
		print_env_declare(shell);
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
