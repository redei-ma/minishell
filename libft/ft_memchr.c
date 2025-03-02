/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:58:08 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:00:44 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;

	str = (unsigned char *)s;
	c = (unsigned char)c;
	while (n--)
	{
		if (*str == c)
			return ((void *)str);
		str++;
	}
	return (NULL);
}

/* int main()
{
	char str[500] = "bonjourno";
	int c = 0;
	int	n = 20;
	char *result_ft = ft_memchr(str, c, n);
    char *result_orig = memchr(str, c, n);

	printf("Funzione ricreata: %s\n", result_ft);
	printf("Funzione originale: %s\n", result_orig);
	return 0;
} */