/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 22:22:02 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void remove_quotes(char **str)
{
	int j;
	int len;
	char quote;

	j = 0;
	len = ft_strlen(*str);
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j];
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			len--;
			while ((*str)[j] && (*str)[j] != quote)
				j++;
			if ((*str)[j] == quote)
			{
				ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
				len--;
			}
		}
		else
			j++;
	}
	*str = ft_realloc(*str, ft_strlen(*str) + 1, len + 1);
}

void    delete_quotes(t_cmd *cmds)
{
	int i;

	while (cmds)
	{
		i = 0;
		remove_quotes(&cmds->cmd);
		while (cmds->args[i])
		{
			remove_quotes(&cmds->args[i]);
			i++;
		}
		cmds = cmds->next;
	}
}
