/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 21:54:48 by renato            #+#    #+#             */
/*   Updated: 2025/03/27 15:19:25 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int			i;
	char		*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

char	*handle_env_variable(char *str, int *i, t_shell *shell)
{
	int			ncv;
	char		*nm_var;
	char		*var_val;

	ncv = *(i) + 1;
	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = malloc((ncv - (*(i) + 1)) + 1);
	if (!nm_var)
		return (NULL);
	ft_strlcpy(nm_var, &str[*(i) + 1], ncv - *(i));
	nm_var[ncv - (*(i) + 1)] = '\0';
	var_val = ft_getenv(nm_var, shell);
	free(nm_var);
	*(i) = ncv;
	if (var_val)
		return (ft_strdup(var_val));
	else
		return (ft_strdup(""));
}

int	handle_exit_status(t_shell *shell)
{
	int			last_exit_status;
	char		*exit_cd;

	last_exit_status = 0;
	exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write_to_fd(shell, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}
