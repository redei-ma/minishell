/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:17:38 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 13:35:12 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipe_manager(t_shell *shell, char **tokens, int *i)
{
	t_pipex	*piper;

	piper = shell->piper;
	if (tokens[*i + 1])
	{
		shell->cmds->next = ft_newcmd(shell);
		piper->fds = ft_realloc(piper->fds, (piper->n_pipes + 1)
				* sizeof(int [2]), (piper->n_pipes + 2) * sizeof(int [2]));
		if (!piper->fds)
			exit_all("Error: malloc failed\n", shell, 1);
		if (pipe(piper->fds[piper->n_pipes]) < 0)
			exit_all("Error: pipe failed\n", shell, 1);
		if (shell->cmds->file_o == -1)
			shell->cmds->file_o = piper->fds[piper->n_pipes][1];
		shell->cmds->next->file_i = piper->fds[piper->n_pipes][0];
		piper->n_pipes++;
		shell->cmds = shell->cmds->next;
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

void	is_valid_env(char **tokens, int i, t_shell *shell)
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

void	parse_cmd(char **tokens, t_shell *shell)
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

void	create_cmds(char **tokens, t_shell *shell)
{
	shell->cmds = ft_newcmd(shell);
	shell->head = shell->cmds;
	parse_cmd(tokens, shell);
	shell->cmds = shell->head;
}
