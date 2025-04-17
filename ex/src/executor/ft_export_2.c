/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 18:39:24 by lacerbi           #+#    #+#             */
/*   Updated: 2025/04/17 12:23:04 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	new_env = ft_calloc(shell->max + 2, sizeof(char *));
	if (!new_env)
	{
		free(n_full_var);
		return (0);
	}
	i = -1;
	while (++i < shell->max)
		new_env[i] = shell->env[i];
	new_env[i] = n_full_var;
	free(shell->env);
	shell->env = new_env;
	shell->max++;
	return (1);
}

void	upd_var(t_shell *shell, const char *nm_var,
	const char *var_val, int eqp)
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
