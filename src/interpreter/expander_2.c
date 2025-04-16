/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:49:18 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/16 13:51:55 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell)
{
	char	*status;

	status = ft_itoa(g_exit_status);
	if (!status)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	*expanded = ft_realloc(*expanded, (iter_arr[2] + 1),
			(iter_arr[2] + ft_strlen(status) - 1) * sizeof(char));
	if (!*expanded)
	{
		free(status);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*expanded + iter_arr[1], status, ft_strlen(status) + 1);
	iter_arr[1] += ft_strlen(status);
	iter_arr[0] += 2;
	iter_arr[2] += ft_strlen(status) - 2;
	free(status);
}

char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int		i;
	char	*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

char	*handle_env_variable(char *str, int *i, t_shell *shell)
{
	int		ncv;
	char	*nm_var;
	char	*var_val;

	ncv = *i + 1;
	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = ft_calloc((ncv - (*i + 1)) + 1, sizeof(char));
	if (!nm_var)
		return (NULL);
	ft_strlcpy(nm_var, &str[*i + 1], ncv - *i);
	var_val = ft_getenv(nm_var, shell);
	free(nm_var);
	*i = ncv;
	if (var_val)
		return (ft_strdup(var_val));
	else
		return (ft_strdup(""));
}
