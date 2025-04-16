/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/16 16:33:58 by redei-ma         ###   ########.fr       */
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
	if (shell->input[0])
		add_history(shell->input);
	if (is_empty(shell) || check_syntax_error(shell->input, shell)
		|| check_unclosed(&shell->input, shell))
		return ;
	set_spaces(&shell->input, shell);
	shell->tokens = ft_minisplit(shell->input);
	if (!shell->tokens)
		exit_all("Error: malloc failed\n", shell, 1);
	tokenizator(shell);
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
	while (1)
		loop_line(shell);
}
