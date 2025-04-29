/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   HD_expander.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:53:05 by lacerbi           #+#    #+#             */
/*   Updated: 2025/04/29 13:53:06 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	HD_var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		x;
	char	*var;
	int		new_len;

	x = iter_arr[0];
	var = handle_env_variable(str, &iter_arr[0], shell, &new_len);
	if (!var)
		var = ft_strdup("");
	if (!var)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	//new_len = iter_arr[1] + ft_strlen(var) + 1;
	new_len = (iter_arr[2] + ft_strlen(var)) - new_len + 1;
	*expanded = ft_realloc(*expanded, iter_arr[2], new_len * sizeof(char));
	if (!*expanded)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*expanded + iter_arr[1], var, ft_strlen(var) + 1);
	iter_arr[1] += ft_strlen(var);
	iter_arr[2] = new_len;
	free(var);
	new_len = 0;
}

void	HD_stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(expanded, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0] + 1]) || str[iter_arr[0] + 1] == '_')
		HD_var_cases(expanded, iter_arr, shell, str);
	else
		*expanded[iter_arr[1]++] = str[iter_arr[0]++];
}

char	*HD_expander(char *str, t_shell *shell)
{
	int		iter_arr[4];
	char	*expanded;

	iter_arr[0] = 0;
	iter_arr[1] = 0;
	iter_arr[2] = ft_strlen(str);
	expanded = ft_calloc((iter_arr[2] + 1), sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	while (str[iter_arr[0]])
	{
		if (str[iter_arr[0]] == '$')
			HD_stoplight(&expanded, iter_arr, shell, str);
		else
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
	}
	free(str);
	return (expanded);
}

