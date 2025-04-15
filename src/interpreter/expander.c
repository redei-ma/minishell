/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by renato            #+#    #+#             */
/*   Updated: 2025/04/14 11:55:42 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell)
{
	char *status;

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

int	handle_exit_status(t_shell *shell)
{
	int		last_exit_status;
	char	*exit_cd;

	last_exit_status = 0;
	exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write_to_fd(shell, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}
