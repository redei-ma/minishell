/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:54:48 by renato            #+#    #+#             */
/*   Updated: 2025/03/21 23:02:53 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(shell->cmds->file_i, var_val, strlen(var_val));
	else
		write(shell->cmds->file_i, "", 0);
	free(nm_var);
	return (ncv);
}

int	handle_exit_status(t_shell *shell)
{
	int last_exit_status = 0;
	char *exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write(shell->cmds->file_i, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}

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

