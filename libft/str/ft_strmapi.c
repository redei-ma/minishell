/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 13:06:12 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/05 17:01:58 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		len;
	int		i;
	char	*dest;

	if (!s)
		return (ft_strdup(""));
	len = ft_strlen(s);
	i = 0;
	dest = ft_calloc(len + 1, sizeof(char));
	if (!dest)
		return (NULL);
	while (i < len)
	{
		dest[i] = f(i, s[i]);
		i++;
	}
	return (dest);
}

/* char to_upper(unsigned int i, char c)
{
    (void)i;  // Ignora l'indice
    return (char)toupper((unsigned char)c);
}

int main()
{
    char *s = "hello world";
    char *result = ft_strmapi(s, to_upper);

    if (result)
    {
        printf("%s\n", result);  // Stampa "HELLO WORLD"
        free(result);             // Libera la memoria allocata
    }
    return 0;
} */
