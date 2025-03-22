/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 01:22:57 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	in_quotes(char **input)
{
	char	*line;
	char	*newline;
	
	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (!line)
		in_quotes(input);
	newline = ft_strjoin(*input, line);
	free(line);
	if (!newline)
	{
		//exit_error
		exit(1);
	}
	free(*input);
	*input = newline;
}


void	check_open_quotes(char **input)
{
	int		i;
	int 	pipe_count;
	char	quote;
	
	i = 0;
	while ((*input)[i])
	{
		pipe_count = 0;
		if (((*input)[i] == '\'' || (*input)[i] == '\"'))
		{
			quote = (*input)[i];
			i++;
			while ((*input)[i] && (*input)[i] != quote)
				i++;
			if (!(*input)[i])
			{
				in_quotes(input);
				i = -1;
			}
		}
		while ((*input)[i] && (*input)[i] == '|')
		{
			pipe_count++;
			i++;
			while ((*input)[i] && ft_isspace((*input)[i]))
				i++;
		}
		if (!(*input)[i] && (pipe_count == 1 || pipe_count == 2))
		{
			in_quotes(input);
			i = -1;
		}
		i++;
	}
}
