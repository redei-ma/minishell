/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 14:40:45 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 14:50:52 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int		i;
	char	*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

char	*handle_env_variable(char *str, int *i, t_shell *shell, int *new_len)
{
	int		ncv;
	char	*nm_var;
	char	*var_val;

	ncv = *i + 1;
	*new_len = ncv - 1;
	if (str[ncv] && ft_isdigit(str[ncv]))
		ncv++;
	else
	{
		while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
			ncv++;
	}
	*new_len = ncv - *new_len;
	nm_var = ft_calloc((ncv - (*i + 1)) + 1, sizeof(char));
	if (!nm_var)
		return (NULL);
	ft_strlcpy(nm_var, &str[*i + 1], ncv - *i);
	var_val = ft_getenv(nm_var, shell);
	free(nm_var);
	*i = ncv;
	if (var_val)
		return (ft_strdup(var_val));
	else
		return (ft_strdup(""));
}
