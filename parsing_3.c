/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 20:40:21 by renato            #+#    #+#             */
/*   Updated: 2025/03/27 15:16:07 by redei-ma         ###   ########.fr       */
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
			while ((*str)[j] != quote)
				j++;
			ft_memmove(*str + j, *str + j + 1, ft_strlen(*str + j));
			new_len--;
		}
		else
			j++;
	}
	*str = ft_realloc(*str, old_len + 1, new_len + 1);
}

void	delete_quotes(t_cmd *cmds, t_shell *shell)
{
	int	i;

	while (cmds)
	{
		i = 0;
		remove_quotes(&cmds->cmd);
		if (!cmds->cmd)
			exit_all("Error: malloc failed\n", shell, 1);
		while (cmds->args && cmds->args[i])
		{
			if (ft_strncmp(cmds->cmd, "echo", 4) != 0)
				remove_quotes(&cmds->args[i]);
			if (!cmds->args[i])
				exit_all("Error: malloc failed\n", shell, 1);
			i++;
		}
		cmds = cmds->next;
	}
}
