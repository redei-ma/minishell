/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 12:49:30 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:01 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*temp;

	temp = (unsigned char *)s;
	while (n--)
	{
		*temp = c;
		temp++;
	}
	return (s);
}

/* int main()
{
	char str1[50] = "Ciao mondo!";
	char str2[50] = "Ciao mondo!";

	memset(str1, 'X', 6);
	ft_memset(str2, 'X', 6);
	printf("Funzione ufficiale:\n%s\n", str1);
	printf("Funzione ricreata:\n%s", str2);
} */