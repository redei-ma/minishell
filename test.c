/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by lacerbi           #+#    #+#             */
/*   Updated: 2025/02/27 13:57:33 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"
/*
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

void	find_cmd(t_shell *shell)
{
	char *cmd;

	*cmd = shell->cmd[shell->i];
	if (is_builtin(cmd))
		exe_builtin(shell); //da fa'
	else if (is_executable(cmd))
		exe_external(shell); //da fa'
	else if (find_in_path(cmd))
		exe_external(shell); //da fa'
	else if (is_redirection(cmd))
		handle_redirection(shell); //da fa'
	else
		ft_printf("minishell: comando non trovato: %s\n", cmd);
}

void	cmd_manage(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		shell->i = i;
		find_cmd(shell);
		i++;	
	}
}
*/

int	main(void)
{
	t_shell	shell;

	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			//exit_good();
			exit(0);
		}
		add_history(shell.input);
		if (!is_empty(shell.input))
		{
			printf("input: %s\n", shell.input);
			add_history(shell.input);
		}
		shell.cmd = ft_nsplit(shell.input);
		if (!shell.cmd)
		{
			//exit_error();
			exit(1);
		}
		free(shell.input);
		int i = 0;
		while (shell.cmd[i])
		{
			printf("cmd[%d]: %s\n", i, shell.cmd[i]);
			i++;
		}
		//cmd_manage(&shell);
		ft_freemat((void **)shell.cmd, ft_matlen(shell.cmd));
	}
	return 0;
}
