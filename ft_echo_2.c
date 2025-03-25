/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:54:48 by renato            #+#    #+#             */
/*   Updated: 2025/03/23 01:28:55 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void write_to_fd(t_shell *shell, const char *str, int len)
{
	int fd;

	if (shell->cmds->file_a == -1 && shell->cmds->file_o == -1)
		fd = 1;
	else if (shell->cmds->file_a != -1)
		fd = shell->cmds->file_a;
	else
		fd = shell->cmds->file_o;
	write(fd, str, len);
}

char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int	i;
	char	*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

int	handle_env_variable(char *str, int i, t_shell *shell)
{
	int ncv = i + 1;
	char *nm_var;
	char *var_val;

	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = malloc((ncv - (i + 1)) + 1);
	if (!nm_var)
		return (-1);
	ft_strlcpy(nm_var, &str[i + 1], ncv - i);
	nm_var[ncv - (i + 1)] = '\0';
	var_val = ft_getenv(nm_var, shell);
	if (var_val)
		write_to_fd(shell, var_val, ft_strlen(var_val));
	else
		write_to_fd(shell, "", 0);
	free(nm_var);
	return (ncv);
}

int	handle_exit_status(t_shell *shell)
{
	int last_exit_status = 0;
	char *exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write_to_fd(shell, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}
