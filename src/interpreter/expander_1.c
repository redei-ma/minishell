/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by redei-ma         #+#    #+#             */
/*   Updated: 2025/05/05 14:05:01 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	var_init(char ***var_split, int *var_sp_len, t_shell *shell, char *var)
{
	*var_split = ft_minisplit(var);
	if (!*var_split)
		exit_all("Error: malloc failed\n", shell, 1);
	*var_sp_len = ft_matlen(*var_split);
	if (*var_sp_len == 1)
	{
		ft_free_char_mat(*var_split);
		return (0);
	}
	shell->tokens = ft_realloc(shell->tokens, (ft_matlen(shell->tokens) + 1)
			* sizeof(char *), (ft_matlen(shell->tokens)
				+ *var_sp_len) * sizeof(char *));
	if (!shell->tokens)
	{
		ft_free_char_mat(*var_split);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	return (1);
}

int	var_size(char *var, int *iter_arr, t_shell *shell)
{
	int		i;
	int		var_sp_len;
	char	**var_split;

	i = ft_matlen(shell->tokens) - 1;
	if (var_init(&var_split, &var_sp_len, shell, var) == 0)
		return (0);
	while (i >= iter_arr[3])
	{
		shell->tokens[i + var_sp_len - 1] = shell->tokens[i];
		i--;
	}
	shell->tokens[iter_arr[3]] = var_split[0];
	i = 1;
	while (i < var_sp_len)
	{
		shell->tokens[iter_arr[3] + i] = var_split[i];
		i++;
	}
	free(var_split);
	iter_arr[3] += var_sp_len - 1;
	return (1);
}

void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		x;
	int		is_isolated;
	int		new_len;
	char	*var;

	x = iter_arr[0];
	var = handle_env_variable(str, &iter_arr[0], shell, &new_len);
	if (!var)
		var = ft_strdup("");
	if (!var)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	is_isolated = (x == 0 || !ft_isalnum(str[x - 1]))
		&& (str[iter_arr[0]] == '\0' || !ft_isalnum(str[iter_arr[0]]));
	if (iter_arr[3] != -1 && ft_strcmp(var, "") != 0
		&& is_isolated && var_size(var, iter_arr, shell))
	{
		free(var);
		free(*expanded);
		return ;
	}
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

void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(expanded, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0] + 1]) || str[iter_arr[0] + 1] == '_')
		var_cases(expanded, iter_arr, shell, str);
	else if (iter_arr[5])
		(*expanded)[iter_arr[1]++] = str[iter_arr[0]++];
	else
		iter_arr[0]++;
}

char	*expander(char *str, int *i, t_shell *shell)
{
	int		iterr[6];
	char	*expanded;

	iterr[0] = 0;
	iterr[1] = 0;
	iterr[2] = ft_strlen(str);
	iterr[3] = *i;
	iterr[4] = 0;
	iterr[5] = 0;
	expanded = ft_calloc((iterr[2] + 1), sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	while (str[iterr[0]])
	{
		if (*i != -404 && (handle_quotes(str[iterr[0]], &iterr[4], &iterr[5])))
			expanded[iterr[1]++] = str[iterr[0]++];
		else if (str[iterr[0]] == '$' && !iterr[4])
		{
			stoplight(&expanded, iterr, shell, str);
			*i = iterr[3];
		}
		else
			expanded[iterr[1]++] = str[iterr[0]++];
	}
	return (free(str), expanded);
}

void	expand_vars(t_shell *shell)
{
	int		i;
	int		j;
	int		pre_len;
	char	*expanded;

	i = -1;
	while (shell->tokens[++i])
	{
		if (i > 0 && shell->tokens[i - 1][0] == '<'
					&& shell->tokens[i - 1][1] == '<')
		{
			remove_quotes(&shell->tokens[i]);
			if (!shell->tokens[i])
				exit_all("Error: malloc failed\n", shell, 1);
			continue ;
		}
		pre_len = ft_matlen(shell->tokens);
		expanded = expander(shell->tokens[i], &i, shell);
		if (pre_len != ft_matlen(shell->tokens))
		{
			i = -1;
			continue ;
		}
		else
			shell->tokens[i] = expanded;
		if (shell->tokens[i][0] == '\0')
		{
			free(shell->tokens[i]);
			j = i;
			while (shell->tokens[j])
			{
				shell->tokens[j] = shell->tokens[j + 1];
				j++;
			}
			i--;
		}
	}
}
