/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:52:54 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/05 16:54:25 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	str_vars(char *str, t_shell *shell)
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

static void	n_finder(int *i, t_shell *shell)
{
	int	x;

	*i = 0;
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
	shell->exit_status = 0;
}
