/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 11:01:32 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:02:24 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 65 && c <= 90)
		c += 32;
	return (c);
}

/* int main()
{
	char a = 90;
	char b = 100;
	printf("Funzione ricreata: %d	%d\n", ft_tolower(a), ft_tolower(b));
	printf("Funzione originale: %d	%d", tolower(a), tolower(b));
	return 0;
} */