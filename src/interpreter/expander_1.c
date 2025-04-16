/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 22:04:35 by renato           ###   ########.fr       */
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
			(iter_arr[2] + ft_strlen(var)
				- (iter_arr[0] - x) + 1) * sizeof(char));
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
	else if (ft_isalnum(str[iter_arr[0] + 1]) || str[iter_arr[0] + 1] == '_')
		var_cases(expanded, iter_arr, shell, str);
	else
		(*expanded)[iter_arr[1]++] = str[iter_arr[0]++];
}

char	*expander(char *str, t_shell *shell)
{
	int		iter_arr[3];
	char	*expanded;

	iter_arr[0] = 0;
	iter_arr[1] = 0;
	iter_arr[2] = ft_strlen(str);
	expanded = ft_calloc(iter_arr[2] + 1, sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	while (str[iter_arr[0]])
	{
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

	i = -1;
	while ((*tokens)[++i])
	{
		// if (i > 0 && (*tokens)[i - 1][0] == '<' && (*tokens)[i - 1][1] == '<')
		// {
		// 	remove_quotes(&(*tokens)[i]);
		// 	if (!(*tokens)[i])
		// 		exit_all("Error: malloc failed\n", shell, 1);
		// 	continue ;
		// }
		(*tokens)[i] = expander((*tokens)[i], shell);
		if ((*tokens)[i][0] != '\0')
			continue ;
		free((*tokens)[i]);
		j = i - 1;
		while ((*tokens)[++j])
			(*tokens)[j] = (*tokens)[j + 1];
		(*tokens)[j] = NULL;
		i--;
	}
}
