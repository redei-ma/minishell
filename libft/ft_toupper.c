/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:53 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:02:28 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 97 && c <= 122)
		c -= 32;
	return (c);
}

/* int main()
{
	char a = 90;
	char b = 100;
	printf("Funzione ricreata: %d	%d\n", ft_toupper(a), ft_toupper(b));
	printf("Funzione originale: %d	%d", toupper(a), toupper(b));
	return 0;
} */
