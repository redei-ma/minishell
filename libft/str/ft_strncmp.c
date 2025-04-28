/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:00:35 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/16 15:55:51 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*ss1;
	unsigned char	*ss2;

	ss1 = (unsigned char *)s1;
	ss2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	while (n && *ss1 && *ss2 && *ss1 == *ss2)
	{
		ss1++;
		ss2++;
		n--;
	}
	if (n)
		return (*ss1 - *ss2);
	return (0);
}

/* int main()
{
	char *s1 = "abcdef";	
	char *s2 = "abc\xfdxx";
	int	n = 19;

	printf("Funzione ricreata: %d\n", ft_strncmp(s1, s2, n));
	printf("Funzione originale: %d\n", strncmp(s1, s2, n));
	return 0;
} */