/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:52:54 by renato            #+#    #+#             */
/*   Updated: 2025/03/26 18:13:11 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_variable(char *str, int i, t_shell *shell)
{
	if (str[i + 1] == '?')
	{
		if (handle_exit_status(shell) == -1)
			return (-1);
		return (i + 2);
	}
	else
		return (handle_env_variable(str, i, shell));
}

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
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i] != '\0')
	{
		if (handle_quotes(str[i], &in_single_quote, &in_double_quote))
			i++;
		else if (str[i] == '$' && !in_single_quote)
		{
			i = handle_variable(str, i, shell);
			if (i == -1)
				return (-1);
		}
		else
		{
			write_to_fd(shell, &str[i], 1);
			i++;
		}
	}
	return (0);
}

int	cmp_echo_flag(char *str)
{
	if (ft_strncmp(str, "-n", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "\"-n\"", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "\"-\"n", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "-\"n\"", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "\'-n\'", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "\'-\'n", ft_strlen(str)) == 0)
		return (1);
	else if (ft_strncmp(str, "-\'n\'", ft_strlen(str)) == 0)
		return (1);
	return (0);
}

void	ft_echo(t_shell *shell)
{
	int	i;

	i = 0;
	if (shell->cmds->args && cmp_echo_flag(shell->cmds->args[i]))
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
		while (shell->cmds->args[i])
		{
			str_vars(shell->cmds->args[i], shell);
			if (shell->cmds->args[i + 1])
				write_to_fd(shell, " ", 1);
			i++;
		}
		write_to_fd(shell, "\n", 1);
	}
}
