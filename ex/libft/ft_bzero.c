/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 10:56:20 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 16:58:31 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

/* int main()
{
    char str1[50] = "Ciao mondo!";
    char str2[50] = "Ciao mondo!";

    bzero(str1, 6);
    ft_bzero(str2, 6);
    printf("Funzione ufficiale:\n%s\n", str1);
    printf("Funzione ricreata:\n%s", str2);

    return 0;
} */