/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:59:11 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:32 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	char	cc;

	str = (char *)s;
	cc = (unsigned char)c;
	while (*str && *str != cc)
		str++;
	if (*str == cc)
		return (str);
	return (NULL);
}

/* int main ()
{
	int c = 'e';
	char *str = "teste";
	char *str1 = ft_strchr(str, 2048);
	char *str2 = strchr(str, 2048);

	printf("Funzione ricreata: %s\n", str1);
	printf("Funzione originale: %s\n", str2);
	return 0;
} */