/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 12:41:46 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_quotes(char **str)
{
	int		j;
	int		old_len;
	int		new_len;
	char	quote;

	j = 0;
	old_len = ft_strlen(*str);
	new_len = old_len;
	while ((*str)[j])
	{
		if ((*str)[j] == '\'' || (*str)[j] == '\"')
		{
			quote = (*str)[j];
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			new_len--;
			while ((*str)[j] && (*str)[j] != quote)
				j++;
			if (!(*str)[j])
				//exit_error();
				exit(1);
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			new_len--;
		}
		else
			j++;
	}
	*str = ft_realloc(*str, old_len + 1, new_len + 1);
}

void	delete_quotes(t_cmd *cmds)
{
	int i;

	while (cmds)
	{
		i = 0;
		remove_quotes(&cmds->cmd);
		while (cmds->args && cmds->args[i])
		{
			if (ft_strncmp(cmds->cmd, "echo", 4) != 0)
				remove_quotes(&cmds->args[i]);
			i++;
		}
		cmds = cmds->next;
	}
}
