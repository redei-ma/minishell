/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:56:34 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 20:10:22 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*dest;
	size_t	tot;

	if (nmemb == 0 || size == 0)
	{
		return (malloc(0));
	}
	tot = nmemb * size;
	if (tot / size != nmemb)
		return (NULL);
	dest = malloc(tot);
	if (dest == NULL)
		return (NULL);
	ft_bzero(dest, tot);
	return (dest);
}

/* int     main()
{
	char	*s1;
	char	*s2;
    size_t	i = 0;
	size_t	j = 0;
	
    s1 = calloc(i, j);
	printf("Funzione originale: %p\n", s1);
    s2 = ft_calloc(i, j);
    printf("Funzione ricreata: %p\n", s2);
	printf("%zu", i);
    return (0);
} */
