/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_freemat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/13 17:25:24 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/19 20:37:17 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	**ft_freemat(void **mat, int size)
{
	void	**tmp;
	int		i;

	i = 0;
	tmp = mat;
	while (i < size)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
		i++;
	}
	free(mat);
	return (NULL);
}
