/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/24 00:21:25 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_freemat(void **mat, int size)
{
	int	i;

	if (!mat)
		return (NULL);
	i = 0;
	while (i < size)
	{
		if (mat[i])
		{
			free(mat[i]);
			mat[i] = NULL;
		}
		i++;
	}
	free(mat);
	return (NULL);
}
