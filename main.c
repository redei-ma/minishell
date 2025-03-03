/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/03 16:07:16 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* void	exe_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->cmd[0], "echo", 4) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->cmd[0], "cd", 2) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->cmd[0], "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->cmd[0], "export", 6) == 0)
		ft_export(shell);
	else if (ft_strncmp(shell->cmd[0], "unset", 5) == 0)
		ft_unset(shell);
	else if (ft_strncmp(shell->cmd[0], "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->cmd[0], "exit", 4) == 0)
		exit_good();
}

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "echo", 4) == 0)
		return 1;
	else if(ft_strncmp(cmd, "cd", 2) == 0)
		return 1;
	else if(ft_strncmp(cmd, "pwd", 3) == 0)
		return 1;
	else if(ft_strncmp(cmd, "export", 6) == 0)
		return 1;
	else if(ft_strncmp(cmd, "unset", 5) == 0)
		return 1;
	else if(ft_strncmp(cmd, "env", 3) == 0)
		return 1;
	else if(ft_strncmp(cmd, "exit", 4) == 0)
		return 1;
	return 0;
}

void	cmd_find(t_shell *shell, int i)
{
	if (is_builtin(shell->cmd[i]))
			exe_builtin(shell);
	else if (is_executable(shell->cmd[i]))
		exe_external(shell);
	else if (is_redirection(shell->cmd[i]))
		handle_redirection(shell);
	else if (is_quotes(shell->cmd[i]))
		handle_quotes(shell);
	else if (is_pipe(shell->cmd[i]))
		handle_pipe(shell);
	else if (is_env(shell->cmd[i]))
		handle_env(shell);
	else if (is_exit_status(shell->cmd[i]))
		handle_exit_status(shell);
	else
		ft_printf("minishell: comando non trovato: %s\n", shell->cmd[i]);
}

void	cmd_manage(t_shell *shell)
{
	int	i;

	i = 0;
	while (shell->cmd[i])
	{
		cmd_find(shell, i);
		i++;
	}
} */

int	main(void)
{
	t_shell	shell;

	// Inizializzazione della libreria readline
	while (1)
	{
		shell.input = readline("minishell> ");
		if (!shell.input)
		{
			//exit_good();
			exit(0);
		}
		if (!is_empty(shell.input))
		{
			ft_printf("input: %s\n", shell.input);
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
			ft_printf("cmd[%d]: %s\n", i, shell.cmd[i]);
			i++;
		}
		//cmd_manage(&shell);
		ft_freemat((void **)shell.cmd, ft_matlen(shell.cmd));
	}
	return 0;
}