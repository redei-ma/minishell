/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:21:56 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:49:13 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*var_creation(const char *nm_var, const char *var_val, int eqp)
{
	char	*temp;
	char	*n_full_var;

	if (var_val && eqp != -1)
	{
		temp = ft_strjoin(nm_var, "=");
		n_full_var = ft_strjoin(temp, var_val);
		free(temp);
		return (n_full_var);
	}
	else
		return (ft_strdup(nm_var));
}

int	srcd_env(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '\0' || shell->env[i][len] == '='))
			return (i);
		i++;
	}
	return (-1);
}

int	update_existing_var(t_shell *shell, int index, char *n_full_var)
{
	free(shell->env[index]);
	shell->env[index] = n_full_var;
	return (1);
}
