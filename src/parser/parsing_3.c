/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/04/11 10:42:44 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

/* void	check_esp_var(char **arg, t_shell *shell)
{
	size_t	i;
	int		in_double;
	int		in_single;

	i = 0;
	in_double = 0;
	in_single = 0;
	while ((*arg)[i])
	{
		handle_quotes((*arg)[i], &in_single, &in_double);
		if (in_single && (*arg)[i] == '$' && ft_isalnum((*arg)[i + 1]))
			return ;
		i++;
	}
	remove_quotes(arg);
	if (!(*arg))
		exit_all("Error: malloc failed\n", shell, 1);
} */

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
			if ((*tokens)[i][j] == '$' && (ft_isalnum((*tokens)[i][j + 1]) || (*tokens)[i][j + 1] == '_' || (*tokens)[i][j + 1] == '?'))
				break ;
			else if (!(*tokens)[i][j + 1])
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
//-----------------------------

// void	remove_spaces(char **input, int *i, char c, t_shell *shell)
// {
// 	int	j;
// 	int	count;
// 	int	old_len;

// 	old_len = ft_strlen(*input);
// 	count = 0;
// 	while ((*input)[*i] && (*input)[*i] == c)
// 	{
// 		count++;
// 		(*i)++;
// 		j = *i;
// 		while ((*input)[j] && ft_isspace((*input)[j]))
// 			j++;
// 		if (j > *i)
// 		{
// 			ft_memmove(*input + *i, *input + j, old_len - j + 1);
// 			*input = ft_realloc(*input, old_len + 1, old_len - (j - *i) + 1);
// 			if (!(*input))
// 				exit_all("Error: malloc failed\n", shell, 1);
// 			old_len -= (j - *i);
// 		}
// 	}
// }

// void	remove_spaces_special_chars(char **input, t_shell *shell)
// {
// 	int	i;

// 	i = 0;
// 	while ((*input)[i])
// 	{
// 		if ((*input)[i] == '|' || (*input)[i] == '<' || (*input)[i] == '>')
// 			remove_spaces(input, &i, (*input)[i], shell);
// 		else
// 			i++;
// 	}
// }
//----------------

int	check_syntax(char *input, char c, t_shell *shell)
{
	int	i;

	i = 0;
	if (*input && *input == c)
		input += 1;
	input += skip_space(input);
	if (!*input)
	{
		return_partial("syntax error near unexpected token `newline'", shell, 2);
		return (1);
	}
	if (input[0] == '>')
	{	
		if (input[1] == '>')
			return_partial("syntax error near unexpected token `>>'", shell, 2);
		else
			return_partial("syntax error near unexpected token `>'", shell, 2);
		return (1);
	}
	if (input[0] == '<')
	{
		while (input[i] == '<')
			i++;
		if (i > 2)
			return_partial("syntax error near unexpected token `<<<'", shell, 2);
		else if (i > 1)
			return_partial("syntax error near unexpected token `<<'", shell, 2);
		else
			return_partial("syntax error near unexpected token `<'", shell, 2);
		return (1);
	}
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

void	check_syntax_error(char *input, t_shell *shell)
{
	int		i;
	int		s;
	char	quote;

	s = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '\"' || input[i] == '\'')
		{
			quote = input[i];
			i++;
			while (input[i] && input[i] != quote)
				i++;
			if (!input[i])
				return ;
			else
				i++;
		}
		if (input[i] == '|')
			s = check_syntax_pipe(input + i + 1, shell); 
		else if (input[i] == '<' || input[i] == '>')
			s = check_syntax(input + i + 1, input[i], shell);
		if (s)
		{
			shell->trigger = 1;
			return ;
		}
		input++;
	}
}
