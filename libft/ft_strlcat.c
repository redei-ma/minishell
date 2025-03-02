/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:59:41 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:47 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	d_len;
	size_t	s_len;

	d_len = ft_strlen(dst);
	s_len = ft_strlen(src);
	if (size <= d_len)
		return (size + s_len);
	else
	{
		i = 0;
		while (src[i] != '\0' && (d_len + i) < size - 1)
		{
			dst[d_len + i] = src[i];
			i++;
		}
		dst[d_len + i] = '\0';
		return (d_len + s_len);
	}
}

/* int main()
{
	char src[] = "body asked you";
	char dest[] = "however, no";
	printf("Funzione ricreata: %zu\n", ft_strlcat(dest, src, 0));
	//printf("Funzione originale: %d", strlcat(dest, src, 10));
	return 0;	
} */