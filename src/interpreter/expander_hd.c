/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_hd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 13:53:05 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 12:03:37 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	var_cases_hd(char **exp, int *iter_arr, t_shell *shell, char *str)
{
	char	*var;
	int		new_len;

	var = handle_env_variable(str, &iter_arr[0], shell, &new_len);
	if (!var)
		var = ft_strdup("");
	if (!var)
	{
		free(*exp);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	new_len = (iter_arr[2] + ft_strlen(var)) - new_len + 1;
	*exp = ft_realloc(*exp, iter_arr[2], new_len * sizeof(char));
	if (!*exp)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*exp + iter_arr[1], var, ft_strlen(var) + 1);
	iter_arr[1] += ft_strlen(var);
	iter_arr[2] = new_len;
	free(var);
	new_len = 0;
}

static void	stoplight_hd(char **exp, int *iter_arr, t_shell *shell, char *str)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(exp, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0] + 1]) || str[iter_arr[0] + 1] == '_')
		var_cases_hd(exp, iter_arr, shell, str);
	else
		*exp[iter_arr[1]++] = str[iter_arr[0]++];
}

char	*expander_hd(char *str, t_shell *shell)
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
			stoplight_hd(&expanded, iter_arr, shell, str);
		else
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
	}
	free(str);
	return (expanded);
}
