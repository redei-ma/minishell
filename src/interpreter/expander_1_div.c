/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/05/06 14:38:02 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

	/*if (shell->tokens[iter_arr[3]])
	free(shell->tokens[iter_arr[3]]);*/

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

int	isolation(int *iter_arr, char *str)
{
	int	x;

	x = iter_arr[0];
	if ((x == 0 || !ft_isalnum(str[x - 1]))
		&& (str[iter_arr[0]] == '\0' || !ft_isalnum(str[iter_arr[0]])))
		return (0);
	else
		return (1);
}

void	append_exp(char **expanded, int *iter_arr, char *var, t_shell *shell)
{
	int		new_len;
	int		var_len;

	var_len = ft_strlen(var);
	new_len = (iter_arr[2] + var_len) - iter_arr[6] + 1;
	*expanded = ft_realloc(*expanded, iter_arr[2], new_len * sizeof(char));
	if (!*expanded)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*expanded + iter_arr[1], var, var_len + 1);
	iter_arr[1] += var_len;
	iter_arr[2] = new_len;
}

void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		is_isolated;
	int		new_len;
	char	*var;

	var = handle_env_variable(str, &iter_arr[0], shell, &new_len);
	if (!var)
		var = ft_strdup("");
	if (!var)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	is_isolated = isolation(iter_arr, str);
	if (iter_arr[3] != -1 && ft_strcmp(var, "") != 0
		&& is_isolated && var_size(var, iter_arr, shell))
	{
		free(var);
		free(*expanded);
		return ;
	}
	iter_arr[6] = new_len;
	append_exp(expanded, iter_arr, var, shell);
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
	int		iterr[7];
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

void	check_size(int *i, int pre_len, char **expanded, t_shell *shell)
{
	int	j;

	if (pre_len != ft_matlen(shell->tokens))
	{
		*i = -1;
		return ;
	}
	else
		shell->tokens[*i] = *expanded;
	if (shell->tokens[*i][0] == '\0')
	{
		free(shell->tokens[*i]);
		j = *i;
		while (shell->tokens[j])
		{
			shell->tokens[j] = shell->tokens[j + 1];
			j++;
		}
		(*i)--;
	}
}

void	expand_vars(t_shell *shell)
{
	int		i;
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
		check_size(&i, pre_len, &expanded, shell);
	}
}
