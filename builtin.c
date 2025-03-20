/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:17:37 by lacerbi           #+#    #+#             */
/*   Updated: 2025/03/19 23:51:15 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *shell, char **envp)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (envp[n])
		n++;
	shell->env = ft_calloc((n + 1), sizeof(char *));
	if (!shell->env)
	{
		free(shell);
		exit(1);
	}
	while(i < n)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
		{
			ft_freemat((void *)shell->env, i);
			free(shell);
			exit(1);
		}
		i++;
	}
	shell->max = n;
}
