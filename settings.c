/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/03/25 20:29:03 by redei-ma         ###   ########.fr       */
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

void	set_shell(t_shell *shell)
{
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
	// ft_printf("1input: %s\n", shell->input);
	if (shell->input)
		add_history(shell->input);
	if (is_empty(shell->input))
		return ;
	remove_spaces_special_chars(&shell->input, shell);
	// ft_printf("2input: %s\n", shell->input);
	set_spaces(&shell->input, shell);
	// ft_printf("3input: %s\n", shell->input);
	shell->tokens = ft_minisplit(shell->input);
	if (!shell->tokens)
		exit_all("Error: malloc failed\n", shell, 1);
	int i = parse_cmds(shell->tokens, shell);
	if (i == 404)
		return_partial(NULL, shell, 1); //errore da capire
	delete_quotes(shell->cmds, shell);
	// ft_print_cmd(shell->cmds);
	cmd_manage(shell);
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
		exit_all("Error: malloc failed\n", shell, 1);
	while (i < n)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			exit_all("Error: malloc failed\n", shell, 1);
		i++;
	}
	shell->max = n;
}
