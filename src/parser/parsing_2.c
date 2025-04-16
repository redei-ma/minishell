/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 17:41:29 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_redir_error(char c, char next, t_shell *shell)
{
	if (c == '>')
	{
		if (next == '>')
			return_partial("syntax error near unexpected token `>>'", shell, 2);
		else
			return_partial("syntax error near unexpected token `>'", shell, 2);
	}
	else if (c == '<')
	{
		if (next == '<')
			return_partial("syntax error near unexpected token `<<'", shell, 2);
		else
			return_partial("syntax error near unexpected token `<'", shell, 2);
	}
}

int	check_syntax_redir(char *input, char c, t_shell *shell)
{
	int	i;

	i = 0;
	if (input[i] == c)
		i++;
	i += skip_space(input);
	if (!input[i])
	{
		return_partial("syntax error near unexpected token `newline'",
			shell, 2);
		return (1);
	}
	if (input[i] == '>' || input[i] == '<')
	{
		print_redir_error(input[i], input[i + 1], shell);
		return (1);
	}
	if (check_syntax_pipe(input + i, shell))
		return (1);
	return (0);
}

int	check_syntax_pipe(char *input, t_shell *shell)
{
	int	i;

	i = skip_space(input);
	if (input[i] && input[i] == '|')
	{
		if (input[i + 1] == '|')
			return_partial("syntax error near unexpected token `||'", shell, 2);
		else
			return_partial("syntax error near unexpected token `|'", shell, 2);
		return (1);
	}
	return (0);
}

void	skip_quotes(char *input, int *i)
{
	char	quote;

	quote = input[*i];
	(*i)++;
	while (input[*i] && input[*i] != quote)
		(*i)++;
}

int	check_syntax_error(char *input, t_shell *shell)
{
	int		i;
	int		s;

	s = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			skip_quotes(input, &i);
			if (!input[i])
				return (0);
			i++;
		}
		if (input[i] == '|')
			s = check_syntax_pipe(input + i + 1, shell);
		else if (input[i] == '<' || input[i] == '>')
			s = check_syntax_redir(input + i + 1, input[i], shell);
		if (s)
			return (1);
		if (input[i])
			i++;
	}
	return (0);
}
