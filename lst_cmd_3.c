/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 15:51:12 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 18:39:23 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_arg(char ***args, char *token)
{
	int count;

	if (!(*args))
	{
		*args = (char **)ft_calloc(2, sizeof(char *));
		if (!*args)
			//exit_error();
			exit(1);
		(*args)[0] = ft_strdup(token);
		if (!(*args)[0])
			//exit_error();
			exit(1);
		return ;
	}
	count = 0;
	while ((*args)[count])
		count++;
	*args = (char **)ft_realloc(*args, (count + 1) * sizeof(char *), (count + 2) * sizeof( char *));
	if (!*args)
		//exit_error();
		exit(1);
	(*args)[count] = ft_strdup(token);
	if (!(*args)[count])
		//exit_error();
		exit(1);
}
