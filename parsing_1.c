/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/24 16:54:29 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_spaces(char **input, int *i, char c, t_shell *shell)
{
	int	j;
	int	count;
	int	old_len;

	old_len = ft_strlen(*input);
	count = 0;
	while ((*input)[*i] && (*input)[*i] == c)
	{
		count++;
		(*i)++;
		j = *i;
		while ((*input)[j] && ft_isspace((*input)[j]))
			j++;
		if (j > *i)
		{
			ft_memmove(*input + *i, *input + j, old_len - j + 1);
			*input = ft_realloc(*input, old_len + 1, old_len - (j - *i) + 1);
			if (!(*input))
				exit_all("Error: malloc failed\n", shell, 1);
			old_len -= (j - *i);
		}
	}
}

void	remove_spaces_special_chars(char **input, t_shell *shell)
{
	int	i;

	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '|')
			remove_spaces(input, &i, '|', shell);
		else if ((*input)[i] == '<')
			remove_spaces(input, &i, '<', shell);
		else if ((*input)[i] == '>')
			remove_spaces(input, &i, '>', shell);
		else
			i++;
	}
}

void	in_quotes(char **input, t_shell *shell)
{
	char	*line;
	char	*newline;

	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (!line)
		exit_all("exit\n", shell, 0);
		// in teoria non dovrebbe mai entrare qui perche e un control C o D
		// in_quotes(input);
	newline = ft_strjoin(*input, line);
	free(line);
	if (!newline)
		exit_all("Error: malloc failed\n", shell, 1);
	free(*input);
	*input = newline;
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
