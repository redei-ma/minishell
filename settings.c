/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/03/22 22:46:53 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_cmd(t_cmd *cmds)
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
}

void	loop_line(t_shell *shell)
{
	shell->input = readline("minishell> ");
	// input = ft_strdup("ls |<i cat -e |e''cho '\"$s' >> file");
	if (!shell->input)
		exit_error("exit\n", shell, 0); // capire se viene chiamato due volte o va bene e se va bene il numero di uscita o se non deve stamapre niente
	check_unclosed(&shell->input, shell);
	if (shell->input)
		add_history(shell->input);
	if(is_empty(shell->input))
		return ;
	set_spaces(&shell->input, shell);
	shel->tokens = ft_minisplit(shell->input);
	if (!shel->tokens)
		exit_error("Error: malloc failed\n", shell, 1);
	parse_cmds(shel->tokens, shell);
	delete_quotes(shell->cmds, shell);
	ft_print_cmd(shell->cmds);
	//cmd_manage(shell);
}

void	init_env(t_shell *shell, char **envp)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (envp[n])
		n++;
	shell->env = ft_calloc((n + 1), sizeof(char *));
	if (!shell->env)
		exit_error("Error: malloc failed\n", shell, 1);
	while(i < n)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			exit_error("Error: malloc failed\n", shell, 1);
		i++;
	}
	shell->max = n;
}

void	set_shell(t_shell *shell, char **envp)
{
	init_env(shell, envp);
	shell->num_heredoc = 0;
	shell->cmds = NULL;
	shell->piper->n_pipes = 0;
	shell->piper->fds = ft_calloc(0, sizeof(int [2]));
	if (!shell->piper->fds)
		exit_error("Error: malloc failed\n", shell, 1);
	shell->piper->pids = ft_calloc(0, sizeof(pid_t));
	if (!shell->piper->pids)
		exit_error("Error: malloc failed\n", shell, 1);
}
