/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:17:38 by renato            #+#    #+#             */
/*   Updated: 2025/03/21 23:46:30 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fileout_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;

	j = 0;
	while (tokens[*i][j] == '>')
		j++;
	if (j == 1 && tokens[++(*i)])
		shell->cmds->file_o = handle_fdout(tokens[*i], 'o');
	else if (j == 2 && tokens[++(*i)])
		shell->cmds->file_a = handle_fdout(tokens[*i], 'a');
	else
		//devo stampare syntax error
		exit(1);
}

void    filein_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;	

	j = 0;
	while (tokens[*i][j] == '<')
		j++;
	if (j == 1 && tokens[++(*i)])
	shell->cmds->file_i = handle_fdin(tokens[*i]);
	else if (j == 2 && tokens[++(*i)])
	shell->cmds->file_i = handle_heredoc(tokens[*i]);
	else
		//devo stampare syntax error
		exit(1);
	
}

void    pipe_manager(t_shell *shell, char **tokens, int *i)
{
	int    j;

	j = 0;
	while(tokens[*i][j] == '|')
		j++;
	if (j > 2)
		//devo stampare i caratterei a indice 2 e 3 in syntax error
		exit(1);
	else if (j > 1)
		//devo stampare il carattere a indice 2 in syntax error
		exit(1);
	else if (tokens[*i + 1])
	{
		shell->cmds->next = ft_newcmd();
		if (!shell->cmds->next)
			// exit_error();
			exit(1);
		shell->piper->fds = ft_realloc(shell->piper->fds, shell->piper->n_pipes * sizeof(int[2]), (shell->piper->n_pipes + 1) * sizeof(int[2]));
		if (!shell->piper->fds)
			//exit_error();
			exit(1);
		if (pipe(shell->piper->fds[shell->piper->n_pipes]) < 0)
			//exit_error();
			exit(1);
		if (shell->cmds->file_o == -1)
			shell->cmds->file_o = shell->piper->fds[shell->piper->n_pipes][1];
		shell->cmds->next->file_i = shell->piper->fds[shell->piper->n_pipes][0];
		shell->piper->n_pipes++;
		shell->cmds = shell->cmds->next;
	}
	// se mi rimane pipe aperta dovrei gestire con GNL e metteregli spazi e tutto
	else
		//exit_error a piacere
		exit(1);
}

t_cmd	*ft_newcmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		//exit_errror();
		exit(1);
	new->cmd = NULL;
	new->args = NULL;
	new->file_i = 1;
	new->file_o = 1;
	new->file_a = 1;
	new->next = NULL;
	return (new);
}

void	parse_cmds(char **tokens, t_shell *shell)
{
	t_cmd	*head;
	int		i;

	i = 0;
	shell->cmds = ft_newcmd();
	if (!shell->cmds)
		//exit_error();
		exit(1);
	head = shell->cmds;
	while (tokens[i])
	{
		if(is_env(tokens[i]))
		{
			if (shell->cmds->cmd)
				add_arg(&shell->cmds->args, tokens[i]);
			else if (!tokens[i + 1] || tokens[i + 1][0] == '|'
					|| tokens[i + 1][0] == '<' || tokens[i + 1][0] == '>')
				shell->cmds->cmd = ft_strdup(tokens[i]);
		}
		else if (tokens[i][0] == '|') // Nuovo comando
			pipe_manager(shell, tokens, &i);
		else if (tokens[i][0] == '<')
			filein_manager(shell, tokens, &i);
		else if (tokens[i][0] == '>')
			fileout_manager(shell, tokens, &i);
		else if (!shell->cmds->cmd)
			shell->cmds->cmd = ft_strdup(tokens[i]);
		else
			add_arg(&shell->cmds->args, tokens[i]);
		if (!tokens[++i])
			break ;
	}
	shell->cmds = head;
}
