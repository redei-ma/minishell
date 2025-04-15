/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/04/15 17:54:36 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_unclosed_pipe(char **input, int *i, t_shell *shell)
{
	int	count;

	count = -1;
	while ((*input)[*i] == '|')
	{
		(*i)++;
		*i += skip_space(*input + *i);
		count++;
	}
	if (!(*input)[*i] && !count)
	{
		return_partial("Syntax error: unclosed pipe", shell, 1);
		return (1);
	}
	return (0);
}

int	find_unclosed_quotes(char **input, int *i, t_shell *shell)
{
	char	quote;

	quote = (*input)[*i];;
	(*i)++;
	while ((*input)[*i] && (*input)[*i] != quote)
		(*i)++;
	if (!(*input)[*i])
	{
		return_partial("Syntax error: unclosed quotes", shell, 1);
		return (1);
	}
	(*i)++;
	return (0);
}

int	check_unclosed(char **input, t_shell *shell)
{
	int	i;

	i = 0;
	while ((*input)[i])
	{
		if (((*input)[i] == '\'' || (*input)[i] == '\"'))
		{
			if (find_unclosed_quotes(input, &i, shell))
				return (1);
		}
		else if ((*input)[i] == '|')
		{
			if (i - skip_space(*input) <= 0)
			{
				if (check_syntax_pipe(*input + i, shell))
					return (1);
			}
			else
				if (find_unclosed_pipe(input, &i, shell))
					return (1);
		}
		else
			i++;
	}
	return (0);
}
