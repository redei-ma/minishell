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

int	skip_space(char *input)
{
	int	i;

	i = 0;
	while (input[i] && ft_isspace(input[i]))
		i++;
	return (i);
}

char	**copy_mat(char **mat, int *max_env, t_shell *shell)
{
	int		i;
	char	**new_mat;

	i = 0;
	while (mat[i])
		i++;
	new_mat = ft_calloc((i + 1), sizeof(char *));
	if (!new_mat)
		exit_all("Error: malloc failed\n", shell, 1);
	i = 0;
	while (mat[i])
	{
		new_mat[i] = ft_strdup(mat[i]);
		if (!new_mat[i])
			exit_all("Error: malloc failed\n", shell, 1);
		i++;
	}
	if (max_env)
		*max_env = i;
	return (new_mat);
}
