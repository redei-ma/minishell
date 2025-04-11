/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/11 13:36:02 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

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
	if (!shell->input)
		exit_all("exit", shell, 0);
	check_unclosed(&shell->input, shell);
	if (shell->input[0])
		add_history(shell->input);
	if (shell->trigger || is_empty(shell->input))
	{
		if (is_empty(shell->input))
			return_partial(NULL, shell, 0);
		else
			return_partial(NULL, shell, shell->trigger);
		return ;
	}
	set_spaces(&shell->input, shell);
	check_syntax_error(shell->input, shell);
	if (shell->trigger)
		return ;
		// Dovrei gestire gli heredoc prima dell syntax error pero non e' stabilito dal subject
	shell->tokens = ft_minisplit(shell->input);
	if (!shell->tokens)
		exit_all("Error: malloc failed\n", shell, 1);
	delete_quotes(&shell->tokens, shell);
	expand_vars(&shell->tokens, shell);
	create_cmds(shell->tokens, shell);
	if (shell->trigger)
	{
		return_partial(NULL, shell, shell->trigger);	
		return ;
	}
	cmd_manage(shell);
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (isatty(STDIN_FILENO))
		interactive_ctrls();
	else
		ni_ctrls();
	(void )av;
	if (ac != 1)
		return (ft_printfd(2, "Error: too many arguments\n"), 1);
	g_exit_status = 0;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (ft_printf("Error: malloc failed"), 1);
	shell->piper = ft_calloc(1, sizeof(t_pipex));
	if (!shell->piper)
		return (free(shell), ft_printfd(2, "Error, Malloc faild"), 1);
	shell->env = copy_mat(envp, &shell->max, shell);
	shell->signal = 0;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	while (1)
		loop_line(shell);
	exit_all("\n\nSi e chiuso il programma\n\n", shell, 0); //da togliere
}
