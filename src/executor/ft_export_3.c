/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:21:56 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:23:02 by renato           ###   ########.fr       */
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
