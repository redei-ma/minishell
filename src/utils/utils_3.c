/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 17:30:54 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/05 17:31:08 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wifexit(void)
{
	int	stat;

	stat = 0;
	while (wait(&stat) > 0)
		;
	if (WIFEXITED(stat))
		return (WEXITSTATUS(stat));
	else if (WIFSIGNALED(stat))
		return (128 + WTERMSIG(stat));
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
