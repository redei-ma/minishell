/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:13:42 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/01 20:27:42 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (!ptr)
		return (ft_calloc(new_size, 1));
	if (new_size == old_size)
		return (ptr);
	new_ptr = ft_calloc(new_size, 1);
	if (!new_ptr)
		return (free(ptr), NULL);
	if (new_size > old_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free (ptr);
	return (new_ptr);
}

/* int main ()
{
	char *prova = ft_calloc(10, 1);
	prova[0] = 'c';
	prova[1] = 'b';
	printf("%s\n", prova);
	prova = ft_realloc(prova, 10, 3);
	printf("%s\n", prova);
} */
