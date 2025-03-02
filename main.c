/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/02 19:27:12 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int is_builtin(char *cmd)
{
	char *builtins[] = {"cd", "echo", "pwd", "export", "unset", "env", "exit", NULL};
	//merdoso
	int i;

	i = 0;
	while (builtins[i])
	{
		if (strcmp(cmd, builtins[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int is_executable(const char *cmd)
{
	struct stat st; //-> struttura che serve a stat per salvarsi le info sul file

	if (stat(cmd, &st) == -1) //check su esistenza del file
		return 0;
//      se file e' regolare     -------------------vari permessi di esecuzione---------------------
	if (S_ISREG(st.st_mode) && (st.st_mode & S_IXUSR || st.st_mode & S_IXGRP || st.st_mode & S_IXOTH))
		return 1;
	
	return 0;
}

void	cmd_manage(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
	if (is_builtin(shell->cmd[i]))
		exe_builtin(shell); //da fa'
	else if (is_executable(cmd))
		exe_external(shell); //da fa'
	else if (is_redirection(shell->cmd[i]))
		handle_redirection(shell); //da fa'
	else if (is_quotes(shell->cmd[i]))
		handle_quotes(shell); //da fa'
	else if (is_pipe(shell->cmd[i]))
		handle_pipe(shell); //da fa'
	else if (is_env(shell->cmd[i]))
		handle_env(shell); //da fa'
	else if (is_exit_status(shell->cmd[i]))
		handle_exit_status(shell); //da fa'
	else
		// ft_printf("minishell: comando non trovato: %s\n", shell->cmd[i]);
		i++;
	}
}

int	main(void)
{
	t_shell	shell;

	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			ft_printfd(1, "exit\n");
			exit_good();
		}
		if (!is_empty(shell.input))
			add_history(shell.input);
		shell.cmd = ft_nsplit(shell.input);
		if (!shell.cmd)
			exit_error();
		free(shell.input);
		cmd_manage(&shell);
		ft_freemat((void **)shell.cmd, ft_matlen((void **)shell.cmd));
	}
	return 0;
}	