/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/05 14:06:39 by redei-ma         ###   ########.fr       */
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
