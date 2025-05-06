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

int	create_new_env_array(t_shell *shell, char *n_full_var)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (shell->max + 2));
	if (!new_env)
	{
		free(n_full_var);
		return (0);
	}
	i = -1;
	while (++i < shell->max)
		new_env[i] = shell->env[i];
	new_env[i] = n_full_var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	shell->max++;
	return (1);
}

int	update_existing_var(t_shell *shell, int index, char *n_full_var)
{
	free(shell->env[index]);
	shell->env[index] = n_full_var;
	return (1);
}

static char	*var_creation(const char *nm_var, const char *var_val, int eqp)
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

void	upd_var(t_shell *shell, char *nm_var, char *var_val, int eqp)
{
	int		index;
	char	*n_full_var;

	n_full_var = var_creation(nm_var, var_val, eqp);
	if (!n_full_var)
		exit_all("Error: malloc failed\n", shell, 1);
	index = srcd_env(shell, nm_var);
	if (index != -1)
		update_existing_var(shell, index, n_full_var);
	else
		create_new_env_array(shell, n_full_var);
}
