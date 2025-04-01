/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:52:54 by renato            #+#    #+#             */
/*   Updated: 2025/04/01 19:05:05 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int	handle_variable(char *str, int i, t_shell *shell)
{
	if (str[i + 1] == '?')
	{
		if (handle_exit_status(shell) == -1)
			return (-1);
		return (i + 2);
	}
	else
		return (handle_env_variable(str, i, shell));
} */

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

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->cmds->args && ft_strcmp(shell->cmds->args[0], "-n") == 0)
	{
		while (shell->cmds->args[i + 1])
		{
			str_vars(shell->cmds->args[i + 1], shell);
			if (shell->cmds->args[i + 2])
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
