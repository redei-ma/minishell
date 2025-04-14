/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:12:06 by renato            #+#    #+#             */
/*   Updated: 2025/03/28 17:49:14 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_special_block(char **input, char *spaced, int *i, int *j)
{
	char	special;

	special = (*input)[*i];
	spaced[(*j)++] = ' ';
	while ((*input)[*i] == special)
		spaced[(*j)++] = (*input)[(*i)++];
	spaced[(*j)++] = ' ';
}

void	update_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

int	count_spec_char(char *input)
{
	int		i;
	int		count;
	char	special;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			special = input[i];
			while (special == input[i] && input[i + 1] == special)
				i++;
			count += 2;
		}
		i++;
	}
	return (count + i + 1);
}

void	set_spaces(char **input, t_shell *shell)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*spaced;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	spaced = ft_calloc(count_spec_char(*input), sizeof(char));
	if (!spaced)
		exit_all("Error: malloc failed\n", shell, 1);
	while ((*input)[i])
	{
		update_quotes((*input)[i], &in_single_quote, &in_double_quote);
		if (((*input)[i] == '|' || (*input)[i] == '>' || (*input)[i] == '<')
			&& !in_single_quote && !in_double_quote)
			copy_special_block(input, spaced, &i, &j);
		else
			spaced[j++] = (*input)[i++];
	}
	free(*input);
	*input = spaced;
}
