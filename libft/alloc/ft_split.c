/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:13 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/02 18:43:55 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (s && *s != '\0')
	{
		if (*s == c)
			flag = 0;
		else if (flag == 0)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	return (count);
}

static char	**ft_cleanmat(char **dest)
{
	char	**tmp;

	tmp = dest;
	while (*tmp)
	{
		free(*tmp);
		*tmp = NULL;
		tmp++;
	}
	free(dest);
	return (NULL);
}

static char	**ft_allocate(char **dest, const char *s, const char c)
{
	char	**start;
	int		n;

	start = dest;
	while (*s)
	{
		while (*s == c)
			s++;
		n = 0;
		while (s[n] != c && s[n] != '\0')
			n++;
		if (n > 0)
		{
			*dest = ft_substr(s, 0, n);
			if (!*dest)
			{
				start = ft_cleanmat(start);
				return (start);
			}
			dest++;
		}
		s += n;
	}
	return (start);
}

char	**ft_split(char const *s, char c)
{
	char		**dest;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s, c);
	dest = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest = ft_allocate(dest, s, c);
	if (!dest)
		return (NULL);
	else
		return (dest);
}

/* int	main()
{
	char	str[] = "hello  fd    fdv df";
	char	c = ' ';
	char	**dest = ft_split(str, c);

	int	i = 0;
	while (dest[i] != NULL)
	{
		printf("%s\n", dest[i]);
        i++;
	}
	dest = ft_cleanmat(dest);
	i--;
	while(i >= 0)
	{
		printf("%s\n", dest[i]);
		i--;
	}
} */