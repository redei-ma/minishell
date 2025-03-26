/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:59:56 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:51 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;

	i = 0;
	if (size == 0)
	{
		while (src[i])
			i++;
		return (i);
	}
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	while (src[i] != '\0')
		i++;
	return (i);
}

/* int main()
{
	char dest1[50] = "Belli ciao";
	//char dest2[50] = "Belli ciao";
	char src[50] = "Brutt ciao ";

	size_t a = ft_strlcpy(dest1, src, 5);
	//size_t b = strlcpy(dest2, src, 5);
	printf("Funzione ricreata: %zu\n", a);
	//printf("Funzione originale: %zu\n", b);
} */