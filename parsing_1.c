/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:33:33 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 20:39:18 by renato           ###   ########.fr       */
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
		//exit_error bash: syntax error: unexpected end of file
		exit(1);
	newline = ft_strjoin(*input, line);
	if (!newline)
	{
		free(line);
		//exit_error
		exit(1);
	}
	free(line);
	free(*input);
	*input = newline;
}


void	check_open_quotes(char **input)
{
	int	i;
	char	quote;
	
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
		{
			quote = (*input)[i];
			i++;
			while ((*input)[i] && (*input)[i] != quote)
				i++;
		}
		if (!(*input)[i])
		{
			i = -1;
			in_quotes(input);
		}
		i++;
	}
}
