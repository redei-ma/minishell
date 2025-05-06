/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 22:02:16 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 14:51:08 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell)
{
	char	*stat;

	stat = ft_itoa(shell->exit_status);
	if (!stat)
	{
		free(*expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	*expanded = ft_realloc(*expanded, (iter_arr[2] + 1),
			(iter_arr[2] + ft_strlen(stat) - 1) * sizeof(char));
	if (!*expanded)
	{
		free(stat);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(*expanded + iter_arr[1], stat, ft_strlen(stat) + 1);
	iter_arr[1] += ft_strlen(stat);
	iter_arr[0] += 2;
	iter_arr[2] += ft_strlen(stat) - 2;
	free(stat);
}

static void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str)
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

static void	check_size(int *i, int pre_len, char **expanded, t_shell *shell)
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

static char	*expander(char *str, int *i, t_shell *shell)
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
