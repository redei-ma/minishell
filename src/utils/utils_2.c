/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:31:03 by redei-ma         #+#    #+#             */
/*   Updated: 2025/05/05 14:06:34 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_printfd_shell(t_shell *shell, const char *format, char *args)
{
	int	fd;

	if (shell->cmds->file_a == -1 && shell->cmds->file_o == -1)
		fd = 1;
	else if (shell->cmds->file_a != -1)
		fd = shell->cmds->file_a;
	else
		fd = shell->cmds->file_o;
	ft_printfd(fd, format, args);
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

int	srcd_env(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0
			&& (shell->env[i][len] == '\0' || shell->env[i][len] == '='))
			return (i);
		i++;
	}
	return (-1);
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

int	skip_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}
