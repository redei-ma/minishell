/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:58:38 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/24 17:07:26 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	*ft_rev(void *dest, const void *src, size_t n)
{
	unsigned char		*tempd;
	unsigned const char	*temps;

	tempd = (unsigned char *)dest + (n - 1);
	temps = (unsigned const char *)src + (n - 1);
	while (n--)
		*tempd-- = *temps--;
	return (dest);
}

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	if (dest == src || n == 0)
		return (dest);
	else if (src > dest)
		return (ft_memcpy(dest, src, n));
	return (ft_rev(dest, src, n));
}

/* int main()
{
	int n = 50;
	char d1[400] = "01234567890123456789";
	char d2[400] = "01234567890123456789";

	printf("Funzione originale: %s\n", (char *)memmove(d1 -2, d1, n));
	printf("Funzione ricreata: %s\n", (char *)ft_memmove(d2 -2, d2, n));
	return 0;
} */