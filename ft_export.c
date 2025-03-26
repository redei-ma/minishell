/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/03/23 00:22:26 by renato           ###   ########.fr       */
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

void	ft_printfd_shell(t_shell *shell, const char *format, char *args)
{
	int	fd;

	if (shell->cmds->file_a == -1 && shell->cmds->file_o == -1)
		fd = 1;
	else if (shell->cmds->file_a != -1)
		fd = shell->cmds->file_a;
	else
		fd = shell->cmds->file_o;
	ft_printfd(fd, format, args);
}

void	print_env_declare(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->env[i])
	{
		ft_printfd_shell(shell, "declare -x %s\n", shell->env[i]);
		i++;
	}
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

/*

void	upd_var(t_shell *shell, const char *nm_var, const char *var_val)
{
	int			index;
	int			i;
	char		*n_full_var;
	char		**new_env;

	i = -1;
	index = srcd_env(shell, nm_var);
	n_full_var = var_creation(nm_var, var_val);
	if (!n_full_var)
		return ;
	if (index != -1)
	{
		free(shell->env[index]);
		shell->env[index] = n_full_var;
	}
	else
	{
		new_env = malloc(sizeof(char *) * (shell->max + 2));
		if (!new_env)
		{
			free(n_full_var);
			return ;
		}
		while (++i < shell->max)
			new_env[i] = shell->env[i];
		new_env[i] = n_full_var;
		new_env[i + 1] = NULL;
		free(shell->env);
		shell->env = new_env;
		shell->max++;
	}
}

void	ft_export(t_shell *shell, char **args)
{
	int			i;
	int			eqp;
	char		*name;
	char		*val;

	if (!args)
	{
		i = 0;
		while (shell->env[i])
		{
			ft_printfd_shell(shell, "declare -x %s\n", shell->env[i]);
			i++;
		}
		return ;
	}
	i = 0;
	while (args[i])
	{
		eqp = find_eq_sn(args[i]);
		if (eqp != -1)
		{
			val = NULL;
			name = ft_substr(args[i], 0, eqp);
			if (name)
			    val = ft_substr(args[i], eqp + 1, ft_strlen(args[i]) - eqp - 1);
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
		else if (srcd_env(shell, args[i]) == -1)
			upd_var(shell, args[i], "");
		i++;
	}
	return ;
}

*/
