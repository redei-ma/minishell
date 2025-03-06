/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:13 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/06 18:05:53 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(const char *s)
{
	int	count;
	int	flag;
	int	quote;

	count = 0;
	flag = 0;
	quote = 1;
	while (s && *s)
	{
		if(*s == 34 || *s == 39)
			quote = -quote;
		if (ft_isspace(*s))
			flag = 0;
		else if (flag == 0 && quote == 1)
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

static char	**ft_allocate(char **dest, const char *s)
{
	char	**start;
	int		n;
	int		quote;

	quote = 1;
	start = dest;
	while (*s)
	{
		n = 0;
		while (ft_isspace(*s))
			s++;
		if (*s == 34 || *s == 39)
			quote = -quote;
		while (s[n] && (!ft_isspace(s[n]) || quote == -1))
		{
			if (s[n] == 34 || s[n] == 39)
				quote = -quote;
			n++;
		}
		if (n > 0)
		{
			*dest = ft_substr(s, 0, n);
			if (!*dest)
				return (ft_cleanmat(start));
			dest++;
		}
		s += n;
	}
	return (start);
}

char	**ft_minisplit(char const *s)
{
	char		**dest;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s);
	dest = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest = ft_allocate(dest, s);
	if (!dest)
		return (NULL);
	else
		return (dest);
}
