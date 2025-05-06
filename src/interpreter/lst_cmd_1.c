/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:17:38 by redei-ma         #+#    #+#             */
/*   Updated: 2025/04/16 13:35:12 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	add_arg(char ***args, char *token, t_shell *shell)
{
	int	count;

	if (!(*args))
	{
		*args = (char **)ft_calloc(2, sizeof(char *));
		if (!*args)
			exit_all("Error: malloc failed\n", shell, 1);
		(*args)[0] = ft_strdup(token);
		if (!(*args)[0])
			exit_all("Error: malloc failed\n", shell, 1);
	}
	else
	{
		count = 0;
		while ((*args)[count])
			count++;
		*args = ft_realloc(*args, (count + 1) * sizeof(char *),
				(count + 2) * sizeof(char *));
		if (!*args)
			exit_all("Error: malloc failed\n", shell, 1);
		(*args)[count] = ft_strdup(token);
		if (!(*args)[count])
			exit_all("Error: malloc failed\n", shell, 1);
	}
}

static void	is_valid_env(char **tokens, int i, t_shell *shell)
{
	if (shell->cmds->cmd)
		add_arg(&shell->cmds->args, tokens[i], shell);
	else if (!tokens[i + 1] || tokens[i + 1][0] == '|'
			|| tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>')
	{
		shell->cmds->cmd = ft_strdup(tokens[i]);
		if (!shell->cmds->cmd)
			exit_all("Error: malloc failed\n", shell, 1);
	}
}

static void	parse_cmd(char **tokens, t_shell *shell)
{
	int	i;

	i = 0;
	while (tokens && tokens[i])
	{
		if (is_env(tokens[i]))
			is_valid_env(tokens, i, shell);
		else if (tokens[i][0] == '|' && shell->tok_type[i] == PIPE)
			pipe_manager(shell, tokens, &i);
		else if (tokens[i][0] == '<' && shell->tok_type[i] == REDIR_IN)
			filein_manager(shell, tokens, &i);
		else if (tokens[i][0] == '>' && shell->tok_type[i] == REDIR_OUT)
			fileout_manager(shell, tokens, &i);
		else if (!shell->cmds->cmd)
		{
			shell->cmds->cmd = ft_strdup(tokens[i]);
			if (!shell->cmds->cmd)
				exit_all("Error: malloc failed\n", shell, 1);
		}
		else
			add_arg(&shell->cmds->args, tokens[i], shell);
		if (!tokens[++i] || shell->trigger)
			break ;
	}
}

t_cmd	*ft_newcmd(t_shell *shell)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		exit_all("Error: malloc failed\n", shell, 1);
	new->cmd = NULL;
	new->args = NULL;
	new->file_i = -1;
	new->file_o = -1;
	new->file_a = -1;
	new->skip = 0;
	new->next = NULL;
	return (new);
}

void	create_cmds(char **tokens, t_shell *shell)
{
	shell->cmds = ft_newcmd(shell);
	shell->head = shell->cmds;
	parse_cmd(tokens, shell);
	shell->cmds = shell->head;
}
