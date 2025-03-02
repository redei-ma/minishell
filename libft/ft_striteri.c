/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:05:36 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:39 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
	{
		f(i, &s[i]);
		i++;
	}
}

/* // Funzione che converte un carattere in maiuscolo
void to_upper(unsigned int i, char *c)
{
    *c = (char)toupper((unsigned char)*c);
}

int main()
{
    char str[] = "hello world";

    // Applica la funzione to_upper a ciascun carattere della stringa
    ft_striteri(str, to_upper);

    printf("%s\n", str);  // Stampa "HELLO WORLD"
    return 0;
} */
