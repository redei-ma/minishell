/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/30 21:14:46 by renato           ###   ########.fr       */
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
		if (line)
			free(line);
		dup2(shell->original_stdin, 0);
		return ; // da capire se devo portaare avanti l'errore o non serve
	}
	if (!line)
	{
		ft_printf("merdeeee\n"); //strivere quello cgha fa bash con ctrl d e capire se devo freare
		return ;
		// exit_all("exit\n", shell, 0);
		// in teoria non dovrebbe mai entrare qui perche e un control C o D
		// in_quotes(input);
	}
	newline = ft_strjoin(*input, line);
	free(line);
	if (!newline)
		exit_all("Error: malloc failed\n", shell, 1);
	free(*input);
	*input = newline;
	signal(SIGINT, handle_ctrl_c);
}

void	find_unclosed_pipe(char **input, int *i, t_shell *shell)
{
	int	pipe_count;

	pipe_count = 0;
	while ((*input)[*i] && (*input)[*i] == '|')
	{
		pipe_count++;
		(*i)++;
		while ((*input)[*i] && ft_isspace((*input)[*i]))
			(*i)++;
	}
	if (!(*input)[*i] && (pipe_count == 1 || pipe_count == 2))
	{
		in_quotes(input, shell);
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
		*i = 0;
	}
	else if ((*input)[*i] == quote)
		(*i)++;
}

void	check_unclosed(char **input, t_shell *shell)
{
	int		i;

	i = 0;
	while ((*input)[i])
	{
		if (((*input)[i] == '\'' || (*input)[i] == '\"'))
			find_unclosed_quotes(input, &i, shell);
		else if ((*input)[i] == '|')
			find_unclosed_pipe(input, &i, shell);
		else
			i++;
	}
}
