/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:13 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/22 02:42:13 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// possibile miglioramento gestione di quote
static size_t	ft_count_words(const char *s)
{
	size_t	count;
	int		in_word;
	char	quote;

	count = 0;
	in_word = 0;
	while (*s)
	{
		while (ft_isspace(*s))
		{
			in_word = 0;
			s++;
		}
		if (!*s)
			break;
		if (!in_word)
		{
			count++;
			in_word = 1;
		}
		if (*s == '"' || *s == '\'')
		{
			quote = *s;
			s++;
			while (*s && *s != quote)
				s++;
			if (*s == quote)
				s++;
		}
		else
		{
			while (*s && !ft_isspace(*s) && *s != '"' && *s != '\'')
				s++;
		}
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
	int		i;
	int		j;
	char	quote;

	j = 0;
	while (*s)
	{
		i = 0;
		while (ft_isspace(*s))
			s++;
		if (!*s)
			break;
		while (s[i] && (!ft_isspace(s[i]) || (i > 0 && s[i - 1] == '\\')))
		{
			if (s[i] == '"' || s[i] == '\'')
			{
				quote = s[i];
				i++;
				while (s[i] && s[i] != quote)
					i++;
				if (s[i] == quote)
					i++;
			}
			else
				i++;
		}
		dest[j] = ft_substr(s, 0, i);
		if (!dest[j])
			return (ft_cleanmat(dest));
		s += i;
		j++;
	}
	return (dest);
}

char	**ft_minisplit(char const *s)
{
	char		**dest;
	size_t		words;

	if (!s)
		return (NULL);
	words = ft_count_words(s);
	if (words == 0)
		return (NULL);
	dest = (char **)ft_calloc(words + 1, sizeof(char *));
	if (!dest)
		return (NULL);
	dest = ft_allocate(dest, s);
	if (!dest)
		return (NULL);
	else
		return (dest);
}

/* int main()
{
	char	**cmd;
	cmd = ft_minisplit("	 c'at' < 'error ciao ' echo -n o''ut 	 $PW'  'D ");
	while(*cmd)
	{
		ft_printf("cmd: %s\n", *cmd);
		cmd++;
	}
	return (0);
} */