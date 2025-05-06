/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:39:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 12:03:37 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_export_value(t_shell *shell, char *arg, int eq_pos)
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

int	is_valid_identifier(char *str)
{
	int	i;

	if (!str || (!ft_isalpha(str[0]) && str[0] != '_'))
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	process_export_arg(t_shell *shell, char *arg)
{
	int	eq_pos;

	if (arg[0] == '=')
	{
		ft_printfd(2, "export: `%s': not a valid identifier\n", arg);
		shell->exit_status = 1;
		return ;
	}
	if (!is_valid_identifier(arg))
	{
		ft_printfd(2, "minishell: export: not a valid identifier\n");
		shell->exit_status = 1;
		return ;
	}
	eq_pos = find_eq_sn(arg);
	if (eq_pos != -1)
		handle_export_value(shell, arg, eq_pos);
	else if (srcd_env(shell, arg) == -1)
		upd_var(shell, arg, "", eq_pos);
	shell->exit_status = 0;
}
