/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:58:29 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/05 14:06:37 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

/* int main ()
{
	char dest1[50] = "Belli ciao";
	char dest2[50] = "Belli ciao";
	char src[50] = "Brutt ciao";

	//ft_memcpy(dest1, src, 5);
	//memcpy(dest2, src, 5);
	//printf("Funzione ricreata: %s\n", ft_memcpy(NULL, src, 5));
	printf("Funzione originale: %s\n", memcpy(NULL, src, 5));
} */