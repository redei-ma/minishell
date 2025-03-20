/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 12:54:40 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 00:57:51 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    pipe_manager(t_shell *shell, char **tokens, int *i)
{
	int    j;

	j = 0;
	while(tokens[*i][j] == '|')
		j++;
	if (j > 2)
		//devo stampare i caratterei a indice 2 e 3 in syntax error
		// exit_error();
		exit(1);
	else if (j > 1)
		//devo stampare il carattere a indice 2 in syntax error
		exit(1);
	/* else if (!tokens[i][1])
		//devo stampare syntax error newline
		exit(1); */
	else if (tokens[*i + 1])
	{
		shell->cmds->next = ft_newcmd();
		if (!shell->cmds->next)
			// exit_error();
			exit(1);
		shell->cmds = shell->cmds->next;
	}
	// se mi rimane pipe aperta dovrei gestire con GNL e metteregli spazi e tutto
	else
		//exit_error a piacere
		exit(1);
}

void    filein_manager(t_shell *shell, char **tokens, int *i)
{
	int	j;	

	shell->piper->n_pipes = 0;
	j = 0;
	while (tokens[*i][j] == '<')
		j++;
	if (j == 1 && tokens[++(*i)])
		handle_fdin(tokens[*i]);
	else if (j == 2 && tokens[++(*i)])
		handle_heredoc(tokens[*i]);
	else
		//devo stampare syntax error
		exit(1);
	
}

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
