/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 18:57:04 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/30 15:32:10 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizator(t_shell *shell)
{
	int	i;

	shell->tok_type = ft_calloc(ft_matlen(shell->tokens), sizeof(int));
	i = 0;
	while (shell->tokens[i])
	{
		if (shell->tokens[i][0] == '|')
			shell->tok_type[i] = PIPE;
		else if (shell->tokens[i][0] == '<')
			shell->tok_type[i] = REDIR_IN;
		else if (shell->tokens[i][0] == '>')
			shell->tok_type[i] = REDIR_OUT;
		else
			shell->tok_type[i] = WORD;
		i++;
	}
}

void	remove_quotes(char **str)
{
	int		j;
	int		old_len;
	int		new_len;
	char	quote;

	j = 0;
	old_len = ft_strlen(*str);
	new_len = old_len;
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j];
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			new_len--;
			while ((*str)[j] != quote)
				j++;
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			new_len--;
		}
		else
			j++;
	}
	*str = ft_realloc(*str, old_len + 1, new_len + 1);
}

void	delete_quotes(char ***tokens, t_shell *shell)
{
	int	i;
	int	j;

	i = 0;
	while ((*tokens)[i])
	{
		j = 0;
		while ((*tokens)[i][j])
		{
			if (!(*tokens)[i][j + 1])
			{
				remove_quotes(&(*tokens)[i]);
				if (!(*tokens)[i])
					exit_all("Error: malloc failed\n", shell, 1);
				break ;
			}
			j++;
		}
		i++;
	}
}
