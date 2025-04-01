/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:39:24 by lacerbi           #+#    #+#             */
/*   Updated: 2025/04/01 17:10:35 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char *var_creation(const char *nm_var, const char *var_val)
{
	if (var_val && *var_val)
	{
		char *temp = ft_strjoin(nm_var, "=");
		char *n_full_var = ft_strjoin(temp, var_val);
		free(temp);
		return n_full_var;
	}
	else
	{
		return ft_strdup(nm_var);
	}
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
			&& shell->env[i][len] == '=')
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

int	create_new_env_array(t_shell *shell, char *n_full_var)
{
	char	**new_env;
	int		i;

	new_env = malloc(sizeof(char *) * (shell->env_max + 2));
	if (!new_env)
	{
		free(n_full_var);
		return (0);
	}
	i = -1;
	while (++i < shell->env_max)
		new_env[i] = shell->env[i];
	new_env[i] = n_full_var;
	new_env[i + 1] = NULL;
	free(shell->env);
	shell->env = new_env;
	shell->env_max++;
	return (1);
}

void	upd_var(t_shell *shell, const char *nm_var, const char *var_val)
{
	int		index;
	char	*n_full_var;

	n_full_var = var_creation(nm_var, var_val);
	if (!n_full_var)
		return ;
	index = srcd_env(shell, nm_var);
	if (index != -1)
		update_existing_var(shell, index, n_full_var);
	else
		create_new_env_array(shell, n_full_var);
}
