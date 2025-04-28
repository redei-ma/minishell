/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/28 17:06:31 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/*
int	var_size(char *var, char *expanded, int *iter_arr, t_shell *shell)
{
	int		var_sp_len;
	int		tok_len;
	int		i;
	char	**var_split;

	tok_len = ft_matlen(shell->tokens);
	var_split = ft_minisplit(var);
	if (!var_split)
	{
		free(expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	var_sp_len = ft_matlen(var_split);
	if (var_sp_len == 1)
	{
		//ft_free_split
		return (0);
	}
	shell->tokens = ft_realloc(shell->tokens, (tok_len + 1) * sizeof(char *),
	(tok_len + var_sp_len) * sizeof(char *));
	if (!shell->tokens)
	{
		free(expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	i = tok_len - 1;
	while (i >= iter_arr[3])
	{
		shell->tokens[i + var_sp_len - 1] = shell->tokens[i];
		i--;
	}
	//free(shell->tokens[iter_arr[3]]);
	shell->tokens[iter_arr[3]] = var_split[0];
	i = 1;
	while (i < var_sp_len)
	{
		shell->tokens[iter_arr[3] + i] = var_split[i];
		i++;
	}
	//free(var_split);
	iter_arr[3] += var_sp_len - 1;
	return (1);
}*/

void ft_free_matrix(char **matrix)
{
    int i = 0;
    if (!matrix) return;
    
    while (matrix[i])
    {
        free(matrix[i]);
        i++;
    }
    free(matrix);
}

int var_size(char *var, int *iter_arr, t_shell *shell)
{
	int     var_sp_len;
	int     tok_len;
	int     i;
	char    **var_split;
	char    **tmp_tokens;

	var_split = ft_minisplit(var);
	if (!var_split)
	{
		exit_all("Error: malloc failed\n", shell, 1);
	}
	var_sp_len = ft_matlen(var_split);
	if (var_sp_len == 1)
	{
		ft_free_matrix(var_split);
		return (0);
	}
	tok_len = ft_matlen(shell->tokens);
	tmp_tokens = ft_realloc(shell->tokens, (tok_len + 1) * sizeof(char *), (tok_len + var_sp_len) * sizeof(char *));
	if (!tmp_tokens)
	{
		ft_free_matrix(var_split);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	shell->tokens = tmp_tokens;
	i = tok_len - 1;
	while (i >= iter_arr[3])
	{
		shell->tokens[i + var_sp_len - 1] = shell->tokens[i];
		i--;
	}
	/*if (shell->tokens[iter_arr[3]])
        free(shell->tokens[iter_arr[3]]);*/
    shell->tokens[iter_arr[3]] = ft_strdup(var_split[0]);
    i = 1;
    while (i < var_sp_len)
    {
        shell->tokens[iter_arr[3] + i] = ft_strdup(var_split[i]);
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
	is_isolated = (x == 0 || !ft_isalnum(str[x - 1]))
			&& (str[iter_arr[0]] == '\0' || !ft_isalnum(str[iter_arr[0]]));
	if (iter_arr[3] != -1 && ft_strcmp(var, "") != 0 && is_isolated && var_size(var, iter_arr, shell))
	{
		free(var);
		return ;
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

void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str, int in_sd_qts)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(expanded, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0] + 1]) || str[iter_arr[0] + 1] == '_')
		var_cases(expanded, iter_arr, shell, str);
	else if (in_sd_qts)
		(*expanded)[iter_arr[1]++] = str[iter_arr[0]++];
	else
		iter_arr[0]++;
}

char	*expander(char *str, int *i, t_shell *shell)
{
	int		iter_arr[4];
	int		in_sd_qts[2];
	char	*expanded;

	iter_arr[0] = 0;
	iter_arr[1] = 0;
	iter_arr[2] = ft_strlen(str);
	iter_arr[3] = *i;
	in_sd_qts[0] = 0;
	in_sd_qts[1] = 0;
	expanded = malloc((iter_arr[2] + 1) * sizeof(char));
	if (!expanded)
		exit_all("Error: malloc failed\n", shell, 1);
	expanded[iter_arr[2]] = '\0';
	while (str[iter_arr[0]])
	{
		if (handle_quotes(str[iter_arr[0]], &in_sd_qts[0], &in_sd_qts[1]))
		{
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
			continue ;
		}
		if (str[iter_arr[0]] == '$' && !in_sd_qts[0])
		{
			stoplight(&expanded, iter_arr, shell, str, in_sd_qts[1]);
			*i = iter_arr[3];
		}
		else
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
	}
	free(str);
	return (expanded);
}

void	expand_vars(t_shell *shell)
{
	int		i = -1;
	int		pre_len;
	char	*expanded;

	while (shell->tokens[++i])
	{
		if (i > 0 && shell->tokens[i - 1][0] == '<' && shell->tokens[i - 1][1] == '<')
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
			for (int j = i; shell->tokens[j]; j++)
				shell->tokens[j] = shell->tokens[j + 1];
			i--;
		}
	}
	//ft_printfd(2, "%s\n%s", shell->tokens[0], shell->tokens[1]);
}
