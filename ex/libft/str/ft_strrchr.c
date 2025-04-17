/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:21 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:02:10 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		s_len;
	char	*str;
	char	cc;

	s_len = ft_strlen(s);
	str = (char *)s + s_len;
	cc = (unsigned char)c;
	while (s_len >= 0 && *str != cc)
	{
		s_len--;
		str--;
	}
	if (*str == cc)
		return (str);
	return (NULL);
}

/* int main ()
{
	int c = '\0';
	char *str = "";
	char *str1 = ft_strrchr(str, c);
	char *str2 = strrchr(str, c);

	printf("Funzione ricreata: %s\n", str1);
	printf("Funzione originale: %s\n", str2);
	return 0;
} */