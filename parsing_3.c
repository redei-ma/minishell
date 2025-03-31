/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/03/30 21:33:38 by renato           ###   ########.fr       */
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

void	delete_quotes(t_cmd *cmds, t_shell *shell)
{
	int	i;

	while (cmds)
	{
		i = 0;
		remove_quotes(&cmds->cmd);
		if (!cmds->cmd)
			exit_all("Error: malloc failed\n", shell, 1);
		while (cmds->args && cmds->args[i])
		{
			if (ft_strncmp(cmds->cmd, "echo", 4) != 0)
				remove_quotes(&cmds->args[i]);
			if (!cmds->args[i])
				exit_all("Error: malloc failed\n", shell, 1);
			i++;
		}
		cmds = cmds->next;
	}
}
//-----------------------------

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
		if ((*input)[i] == '|' || (*input)[i] == '<' || (*input)[i] == '>')
			remove_spaces(input, &i, (*input)[i], shell);
		else
			i++;
	}
}
//----------------

int	check_syntax(char *input, char c)
{
	size_t	i;

	i = 0;
	if (*input && *input == c)
		input += 1;
	input += skip_space(input);
	if (!*input)
	{
		ft_printfd(2, "syntax error near unexpected token `newline'");
		return (1);
	}
	if (input[0] == '>')
	{	
		if (input[1] == '>')
			ft_printfd(2, "syntax error near unexpected token `>>'");
		else
			ft_printfd(2, "syntax error near unexpected token `>'");
		return (1);
	}
	if (input[0] == '<')
	{
		while (input[i] == '<')
			i++;
		if (i > 2)
			ft_printfd(2, "syntax error near unexpected token `<<<'");
		else if (i > 1)
			ft_printfd(2, "syntax error near unexpected token `<<'");
		else
			ft_printfd(2, "syntax error near unexpected token `<'");
		return (1);
	}
	//controllare gli altri mi pare sinao uguali per tutti 
	return (0);
}

int	check_syntax_pipe(char *input, char c)
{
	size_t	i;

	i = skip_space(input);
	if (input[i] && input[i] == c)
	{
		if (input[i + 1] && input[i + 1] == '|')
			ft_printfd(2, "syntax error near unexpected token `||'");
		else
			ft_printfd(2, "syntax error near unexpected token `|'");
		return (1);
	}
	return (0);
}

int	skip_space(char *input)
{
	size_t	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

void	check_syntax_error(char *input, t_shell *shell)
{
	size_t	i;
	int		s;

	s = 0;
	i = 0;
	while (input[i])
	{
		if (input[i] == '|')
		{
			if (i - skip_space(input) <= 0)
			{
				if (input[i + 1] && input[i + 1] == '|')
					ft_printfd(2, "syntax error near unexpected token `||'");
				else
					ft_printfd(2, "syntax error near unexpected token `|'");
			}
			s = check_syntax_pipe(input + i + 1, input[i]); 
		}
		else if (input[i] == '<' || input[i] == '>')
			s = check_syntax(input + i + 1, input[i]);
		if (s)
		{
			shell->trigger = 1;
			return ;
		}
		input++;
	}
}
