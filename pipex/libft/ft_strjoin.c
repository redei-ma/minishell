/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:42 by redei-ma          #+#    #+#             */
/*   Updated: 2024/12/11 19:43:43 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	unsigned int	len_s1;
	unsigned int	len;
	char			*dest;

	len_s1 = ft_strlen(s1);
	len = len_s1 + ft_strlen(s2) + 1;
	dest = ft_calloc(len, 1);
	if (!dest)
		return (NULL);
	ft_strlcpy(dest, s1, len_s1 + 1);
	ft_strlcat(dest, s2, len);
	return (dest);
}

/*int main()
{
	char *str1 = "Ciao b";
	char *str2 = "elli";
	char *dest = ft_strjoin(str1, str2);
	printf("Nuova stringa: %s", dest);
	return 0;
} */
