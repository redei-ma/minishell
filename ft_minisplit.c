/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minisplit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:47:13 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/24 16:58:56 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// possibile miglioramento gestione di quote
static size_t	skip_quotes(const char *s)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = s[i];
	i++;
	while (s[i] && s[i] != quote)
		i++;
	if (s[i] == quote)
		i++;
	return (i);
}

static size_t	skip_space(const char *s, int *in_word)
{
	size_t	i;

	i = 0;
	while (s[i] && ft_isspace(s[i]))
		i++;
	if (in_word && i > 0)
		*in_word = 0;
	return (i);
}

static size_t	ft_count_words(const char *s)
{
	size_t	count;
	int		in_word;

	count = 0;
	in_word = 0;
	while (*s)
	{
		s += skip_space(s, &in_word);
		if (!*s)
			break ;
		if (!in_word)
		{
			count++;
			in_word = 1;
		}
		if (*s == '"' || *s == '\'')
			s += skip_quotes(s);
		else
		{
			while (*s && !ft_isspace(*s) && *s != '"' && *s != '\'')
				s++;
		}
	}
	return (count);
}

static char	**ft_allocate(char **dest, const char *s)
{
	int		i;
	int		j;

	j = 0;
	while (*s)
	{
		i = 0;
		s += skip_space(s, NULL);
		if (!*s)
			break ;
		while (s[i] && (!ft_isspace(s[i])))
		{
			if (s[i] == '"' || s[i] == '\'')
				i += skip_quotes(s + i);
			else
				i++;
		}
		dest[j] = ft_substr(s, 0, i);
		if (!dest[j])
			return (ft_free_char_mat(dest));
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
		ft_printf("token: %s\n", *cmd);
		cmd++;
	}
	return (0);
} */