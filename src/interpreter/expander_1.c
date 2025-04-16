/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 13:49:33 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		x;
	char	*var;

	x = iter_arr[0];
	var = handle_env_variable(str, &iter_arr[0], shell);
	if (!var)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	*expanded = ft_realloc(*expanded, (iter_arr[2] + 1),
		(iter_arr[2] + ft_strlen(var) - (iter_arr[0] - x) + 1) * sizeof(char));
	if (!*expanded)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*expanded + iter_arr[1], var, ft_strlen(var) + 1);
	iter_arr[1] += ft_strlen(var);
	free(var);
}

void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(expanded, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0]+1]) || str[iter_arr[0]+1] == '_')
		var_cases(expanded, iter_arr, shell, str);
	else
		(*expanded)[iter_arr[1]++] = str[iter_arr[0]++];
}

char	*expander(char *str, t_shell *shell, int qts_yon)
{
	int		iter_arr[3];
	int		in_sd_qts[2];
	char	*expanded;

	iter_arr[0] = 0;
	iter_arr[1] = 0;
	iter_arr[2] = ft_strlen(str);
	in_sd_qts[0] = 0;
	in_sd_qts[1] = 0;
	expanded = ft_calloc(iter_arr[2] + 1, sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	while (str[iter_arr[0]])
	{
		if (qts_yon != 1 && handle_quotes(str[iter_arr[0]], &in_sd_qts[0], &in_sd_qts[1]))
		{
			iter_arr[0]++;
			continue;
		}
		if (str[iter_arr[0]] == '$' && !in_sd_qts[0])
			stoplight(&expanded, iter_arr, shell, str);
		else
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
	}
	free(str);
	return (expanded);
}

void	expand_vars(char ***tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i])
	{
		if (i > 0 && ((*tokens)[i - 1][0] == '<' && (*tokens)[i - 1][1] == '<'))
		{
			remove_quotes(&(*tokens)[i]);
			if (!(*tokens)[i])
				exit_all("Error: malloc failed\n", shell, 1);
			i++;
			continue;
		}
		(*tokens)[i] = expander((*tokens)[i], shell, 1);
		if ((*tokens)[i][0] == '\0')
		{
			free((*tokens)[i]);
			j = i;
			while ((*tokens)[j])
			{
				(*tokens)[j] = (*tokens)[j + 1];
				j++;
			}
			(*tokens)[j] = NULL;
			i--;
		}
		i++;
	}
}
