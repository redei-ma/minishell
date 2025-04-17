/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/17 17:59:05 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int	var_size(char *var, char *expanded, int *iter_arr, t_shell *shell)
// {
// 	char	**var_split;
// 	int		var_sp_len;
// 	int		tok_len;

// 	tok_len = ft_matlen(shell->tokens);
// 	var_split = ft_minisplit(var);
// 	if (!var_split)
// 	{
// 		free(expanded);
// 		exit_all("Error: malloc failed\n", shell, 1);
// 	}
// 	var_sp_len = ft_matlen(var_split);
// 	if (var_sp_len == 1)
// 		return (0);
// 	shell->tokens = ft_realloc(shell->tokens, (tok_len + 1) * sizeof(char *),
// 			(tok_len + var_sp_len) * sizeof(char *));
// 	if (!shell->tokens)
// 	{
// 		free(expanded);
// 		exit_all("Error: malloc failed\n", shell, 1);
// 	}
// 	int i = var_sp_len - 1;
// 	while (i > 0)
// 	{
// 		shell->tokens[tok_len + var_sp_len] = shell->tokens[tok_len];
// 		tok_len--;
// 		i--;
// 	}
// 	i = 1;
// 	free(shell->tokens[iter_arr[3]]);
// 	shell->tokens[iter_arr[3]] = var_split[0];
// 	while (i < var_sp_len)
// 	{
// 		shell->tokens[iter_arr[3] + i] = var_split[i];
// 		i++;
// 	}
// 	free(var_split);
// 	iter_arr[3] += var_sp_len - 1;
// 	return (1);
// }

void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		x;
	char	*var;
	int		new_len;

	x = iter_arr[0];
	var = handle_env_variable(str, &iter_arr[0], shell);
	// ft_printfd(2, "Var: %s\n", var);
	if (!var)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	// if (iter_arr[3] != -1 && var_size(var, *expanded, iter_arr, shell))
	// {
	// 	ft_printfd(2, "CIAOOOOOOOOOOOOO");
	// 	free(var);
	// 	return ;
	// }
	new_len = iter_arr[1] + ft_strlen(var) + 1;
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

char	*expander(char *str, int *i, t_shell *shell)
{
	int		iter_arr[4];
	char	*expanded;

	iter_arr[0] = 0;
	iter_arr[1] = 0;
	iter_arr[2] = ft_strlen(str);
	iter_arr[3] = *i;
	expanded = ft_calloc(iter_arr[2] + 1, sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	while (str[iter_arr[0]])
	{
		if (str[iter_arr[0]] == '$')
		{
			stoplight(&expanded, iter_arr, shell, str);
			*i = iter_arr[3];
		}
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
		if (i > 0 && (*tokens)[i - 1][0] == '<' && (*tokens)[i - 1][1] == '<')
		{
			remove_quotes(&(*tokens)[i]);
			if (!(*tokens)[i])
				exit_all("Error: malloc failed\n", shell, 1);
			continue ;
		}
		// ft_printfd(2, "Expanding: %s\n", (*tokens)[i]);
		(*tokens)[i] = expander((*tokens)[i], &i, shell);
		// ft_printfd(2, "Token 1: %s\n", (*tokens)[0]);
		// ft_printfd(2, "Token 2: %s\n", (*tokens)[1]);
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
