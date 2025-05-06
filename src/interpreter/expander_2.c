/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 13:49:18 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 15:05:13 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	append_exp(char **exp, int *iter_arr, char *var, t_shell *shell)
{
	int		new_len;
	int		var_len;

	var_len = ft_strlen(var);
	new_len = (iter_arr[2] + var_len) - iter_arr[6] + 1;
	*exp = ft_realloc(*exp, iter_arr[2], new_len * sizeof(char));
	if (!*exp)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*exp + iter_arr[1], var, var_len + 1);
	iter_arr[1] += var_len;
	iter_arr[2] = new_len;
}

static int	var_init(char ***var_split, int *sp_len, t_shell *shell, char *var)
{
	*var_split = ft_minisplit(var);
	if (!*var_split)
		exit_all("Error: malloc failed\n", shell, 1);
	*sp_len = ft_matlen(*var_split);
	if (*sp_len == 1)
	{
		ft_free_char_mat(*var_split);
		return (0);
	}
	shell->tokens = ft_realloc(shell->tokens, (ft_matlen(shell->tokens) + 1)
			* sizeof(char *), (ft_matlen(shell->tokens)
				+ *sp_len) * sizeof(char *));
	if (!shell->tokens)
	{
		ft_free_char_mat(*var_split);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	return (1);
}

static int	var_size(char *var, int *iter_arr, t_shell *shell)
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

static int	isolation(int *iter_arr, char *str)
{
	int	x;

	x = iter_arr[0];
	if ((x == 0 || !ft_isalnum(str[x - 1]))
		&& (str[iter_arr[0]] == '\0' || !ft_isalnum(str[iter_arr[0]])))
		return (0);
	else
		return (1);
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
