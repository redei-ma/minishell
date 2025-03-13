/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/13 15:59:36 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	exe_builtin(t_shell *shell)
{
	if (ft_strncmp(shell->cmds->cmd, "echo", 4) == 0)
		ft_echo(shell);
	else if (ft_strncmp(shell->cmds->cmd, "cd", 2) == 0)
		ft_cd(shell);
	else if (ft_strncmp(shell->cmds->cmd, "pwd", 3) == 0)
		ft_pwd();
	else if (ft_strncmp(shell->cmds->cmd, "export", 6) == 0)
		ft_export(shell);
	else if (ft_strncmp(shell->cmds->cmd, "unset", 5) == 0)
		ft_unset(shell);
	else if (ft_strncmp(shell->cmds->cmd, "env", 3) == 0)
		ft_env(shell);
	else if (ft_strncmp(shell->cmds->cmd, "exit", 4) == 0)
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

/* void	cmd_find(t_shell *shell)
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
} */
		
void	cmd_manage(t_cmd *cmds)
{
	while (shell->cmds)
	{
		if (is_builtin(shell->cmds->cmd))
			exe_builtin(shell);
		else if (is_executable(shell->cmds->cmd))
			exe_external(shell);
		else if (is_redirection(shell->cmds->cmd))
			handle_redirection(shell);
		else if (is_quotes(shell->cmds->cmd))
			handle_quotes(shell);
		// else if (is_pipe(shell->cmds->cmd))
		// 	handle_pipe(shell);
		else if (is_env(shell->cmds->cmd))
			handle_env(shell);
		else if (is_exit_status(shell->cmds->cmd))
			handle_exit_status(shell);
		else
			ft_printf("minishell: comando non trovato: %s\n", shell->cmds->cmd);
		shell->cmds = shell->cmds->next;
	}
}


void	loop_line(t_shell *shell)
{
	char	*input;
	char	**tokens;
	t_cmd	*cmds;

	input = readline("minishell> ");
	if (!input)
		//funzione exit
		exit(0);
	/* if (!is_empty(input))
		add_history(input); */
	if (input)
		add_history(input);
	tokens = ft_minisplit(input);
	if (!tokens)
		// exit_error();
		exit(1);
	cmds = parse_cmds(tokens, shell);
	if (!cmds)
		// exit_error();
		exit(1);
	free(input);
	ft_freemat((void **)mat, ft_matlen(mat));

	cmd_manage(cmds);
	/* int i = 0;
	while (shell->mat[i])
	{
		ft_printf("cmd: %s\n", shell->mat[i]);
		i++;	
	} */
	free_all(); //cmd e shell
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (ac != 1)
		return (ft_printf("minishell: too many arguments\n"));
	av = NULL;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (1);
	shell->tot_pipe = 0;
	init_env(shell, envp);
	loop_line(shell);
	return 0;
}