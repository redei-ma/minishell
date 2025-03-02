/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:59:21 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:35 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char		*dest;
	size_t		len;

	len = ft_strlen(src);
	dest = (char *)malloc(len * sizeof (char) + 1);
	if (dest == NULL)
		return (NULL);
	ft_memcpy(dest, src, len);
	dest[len] = '\0';
	return (dest);
}

/* int main(void)
{
	char *src = "ciao mondo";
	char *dest1 = ft_strdup(src);
	char *dest2 = strdup(src);
	printf("Funzione ricreata: %s\n", dest1);
	printf("Funzione originale: %s\n", dest2);
	free (dest1);
	free (dest2);
	return 0;
} */