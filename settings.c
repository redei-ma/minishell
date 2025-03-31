/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/03/30 21:16:08 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_print_cmd(t_cmd *cmds)
{
	while (cmds)
	{
		int i = 0;
		ft_printf("cmd: %s\n", cmds->cmd ? cmds->cmd : "(null)");
		ft_printf("args: ");
		if (cmds->args)
		{
			while (cmds->args[i])
				ft_printf("%s, ", cmds->args[i++]);
		}
		ft_printf("\n");
		ft_printf("file_i: %d\n", cmds->file_i);
		ft_printf("file_o: %d\n", cmds->file_o);
		ft_printf("file_a: %d\n", cmds->file_a);
		ft_printf("\n");
		cmds = cmds->next;
	}
} */

void	set_shell(t_shell *shell)
{
	shell->trigger = 0;
	shell->cmds = NULL;
	shell->heredocs = ft_calloc(1, sizeof(char *));
	if (!shell->heredocs)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->num_heredoc = 0;
	shell->piper->fds = ft_calloc(1, sizeof(int [2]));
	if (!shell->piper->fds)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->piper->n_pipes = 0;
	shell->piper->pids = ft_calloc(1, sizeof(pid_t));
	if (!shell->piper->pids)
		exit_all("Error: malloc failed\n", shell, 1);
	shell->piper->n_pids = 0;
}

void	loop_line(t_shell *shell)
{
	set_shell(shell);
	shell->input = readline("minishell> ");
	// shell->input = ft_strdup("ls | ");
	if (!shell->input)
		exit_all("exit", shell, 0); // capire se viene chiamato due volte o va bene e se va bene il numero di uscita o se non deve stamapre niente
	check_unclosed(&shell->input, shell);
	if (shell->input[0])
		add_history(shell->input);
	if (is_empty(shell->input))
		return ;
	set_spaces(&shell->input, shell);
	check_syntax_error(shell->input, shell);
	if (shell->trigger)
	{
		//capire se lo esegue. su mac mi pare che se sia prima lo fa senno no
		// exec_heredoc(); // da fare
		return_partial(NULL, shell, 1);
	}
	shell->tokens = ft_minisplit(shell->input);
	if (!shell->tokens)
		exit_all("Error: malloc failed\n", shell, 1);
	create_cmds(shell->tokens, shell);
	if (shell->trigger)
	{
		rl_on_new_line(); // serve?
		return_partial(NULL, shell, 1); // errore da capire
	}
	delete_quotes(shell->cmds, shell);
	cmd_manage(shell);
}

