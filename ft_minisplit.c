/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 11:44:50 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/04 13:08:34 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static size_t	ft_count_words(const char *s)
{
	int	count;
	int	flag;

	count = 0;
	flag = 0;
	while (s && *s)
	{
		if (*s == 34)
		{
			s++;
			while (*s != 34 && *s)
				s++;
		}
		else if (*s == 39)
		{
			s++;
			while (*s != 39 && *s)
				s++;
		}
		if (ft_isspace(*s))
			flag = 0;
		else if (flag == 0)
		{
			count++;
			flag = 1;
		}
		s++;
	}
	printf("count: %d\n", count);
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

	start = dest;
	while (*s)
	{
		n = 0;
		while (ft_isspace(*s))
			s++;
		if (*s == 34)
		{
			s++;
			while (s[n] != 34 && s[n])
				n++;
			n += 2;
			s--;
		}
		else if (*s == 39)
		{
			s++;
			while (s[n] != 39 && s[n])
				n++;
			n += 2;
			s--;
		}
		else
		{
			while (s[n] && !ft_isspace(s[n]))
				n++;
			if (s[n] == 34)
			{
				while (s[n] != 34 && s[n])
					n++;
			}
			else if (s[n] == 39)
			{
				while (s[n] != 39 && s[n])
					n++;
			}
			while (s[n] && !ft_isspace(s[n]))
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

int main(int ac, char **av)
{
	char	**cmd;
	int		i;

	if (ac != 2)
		return (1);
	i = 0;
	cmd = ft_minisplit(av[1]);
	while (cmd[i])
	{
		printf("cmd[%d]: %s\n", i, cmd[i]);
		i++;
	}
	return (0);
}
