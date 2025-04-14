/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/04/14 12:49:50 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_quotes(char **input, t_shell *shell)
{
	char	*line;
	char	*newline;

	signal(SIGINT, handle_ctrl_c_get);
	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (g_exit_status == 130)
	{
		// if (line)
		// 	free(line);
		// dup2(shell->original_stdin, 0);
		shell->trigger = 130;
		return ;
	}
	if (!line)
	{
		shell->trigger = 404;
		return ;
	}
	newline = ft_strjoin(*input, line);
	free(line);
	if (!newline)
		exit_all("Error: malloc failed\n", shell, 1);
	free(*input);
	*input = newline;
}

void	find_unclosed_pipe(char **input, int *i, t_shell *shell)
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
		in_quotes(input, shell);
		signal(SIGINT, handle_ctrl_c);
		if (shell->trigger)
			return ;
		*i = 0;
	}
}

void	find_unclosed_quotes(char **input, int *i, t_shell *shell)
{
	char	quote;

	quote = (*input)[*i];
	(*i)++;
	while ((*input)[*i] && (*input)[*i] != quote)
		(*i)++;
	if (!(*input)[*i])
	{
		in_quotes(input, shell);
		signal(SIGINT, handle_ctrl_c);
		if (shell->trigger)
			return ;
		*i = 0;
	}
	else if ((*input)[*i] == quote)
		(*i)++;
}

void	check_unclosed(char **input, t_shell *shell)
{
	int	i;

	i = 0;
	while ((*input)[i])
	{
		if (((*input)[i] == '\'' || (*input)[i] == '\"'))
			find_unclosed_quotes(input, &i, shell);
		else if ((*input)[i] == '|')
		{
			if (i - skip_space(*input) <= 0)
			{
				if (check_syntax_pipe(*input + i, shell))
				{
					shell->trigger = 2;
					return ;
				}
			}
			else
				find_unclosed_pipe(input, &i, shell);
		}
		else
			i++;
		if (shell->trigger)
		{
			if (shell->trigger == 404)
			{
				ft_printfd(2, "syntax error: unexpected end of file\n");
				shell->trigger = 2;	
			}
			return ;
		}
	}
}
