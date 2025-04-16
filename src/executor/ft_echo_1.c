/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:52:54 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 13:41:50 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (1);
	}
	else if (c == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (1);
	}
	return (0);
}

void	write_to_fd(t_shell *shell, const char *str, int len)
{
	int	fd;

	if (shell->cmds->file_a == -1 && shell->cmds->file_o == -1)
		fd = 1;
	else if (shell->cmds->file_a != -1)
		fd = shell->cmds->file_a;
	else
		fd = shell->cmds->file_o;
	write(fd, str, len);
}

int	str_vars(char *str, t_shell *shell)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		write_to_fd(shell, &str[i], 1);
		i++;
	}
	return (0);
}

void	n_finder(int *i, t_shell *shell)
{
	int	x;

	while (shell->cmds->args && shell->cmds->args[(*i)][0] == '-'
		&& shell->cmds->args[(*i)][1] == 'n')
	{
		x = 2;
		while (shell->cmds->args[*i][x] == 'n')
			x++;
		if (!shell->cmds->args[*i][x])
		{
			(*i)++;
			if (!shell->cmds->args[*i])
				return ;
		}
		else
			break ;
	}
}

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 0;
	n_finder(&i, shell);
	if (shell->cmds->args && i > 0)
	{
		while (shell->cmds->args[i])
		{
			str_vars(shell->cmds->args[i], shell);
			if (shell->cmds->args[i + 1])
				write_to_fd(shell, " ", 1);
			i++;
		}
	}
	else
	{
		while (shell->cmds->args && shell->cmds->args[i])
		{
			str_vars(shell->cmds->args[i], shell);
			if (shell->cmds->args[i + 1])
				write_to_fd(shell, " ", 1);
			i++;
		}
		write_to_fd(shell, "\n", 1);
	}
}
