/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:23:27 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/17 17:59:08 by redei-ma         ###   ########.fr       */
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

int	is_env(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && (ft_isalnum(cmd[i]) || cmd[i] == '_'))
		i++;
	if (cmd[i] && cmd[i] == '=' && i > 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (1);
	else if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	else if (ft_strcmp(cmd, "export") == 0)
		return (1);
	else if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	else if (ft_strcmp(cmd, "env") == 0)
		return (1);
	else if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	ft_cmd_size(t_cmd *lst)
{
	t_cmd	*tmp;
	int		count;

	tmp = lst;
	count = 0;
	while (tmp)
	{
		tmp = tmp->next;
		count++;
	}
	return (count);
}

int	is_empty(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->input[i] && ft_isspace(shell->input[i]))
		i++;
	if (shell->input[i])
		return (0);
	return_partial(NULL, shell, 0);
	return (1);
}
