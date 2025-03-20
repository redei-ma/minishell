/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 22:22:06 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void ft_print_cmd(t_cmd *cmds)
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
	char	*input;
	char	**tokens;

	input = readline("minishell> ");
	//input = ft_strdup("ls -l");
	if (!input)
		//funzione exit (bisogna anche eliminare gli heredoc creati)
		exit(0);
	/* if (!is_empty(input))
		add_history(input); */
	check_open_quotes(&input);
	if (input)
		add_history(input);
	if(is_empty(input))
		return ;
	set_spaces(&input);
	tokens = ft_minisplit(input);
	if (!tokens)
		// exit_error();
		exit(1);
	parse_cmds(tokens, shell);
	delete_quotes(shell->cmds);

	free(input);
	ft_freemat((void **)tokens, ft_matlen(tokens));

	ft_print_cmd(shell->cmds);
	//cmd_manage(cmds);
	/* int i = 0;
	while (shell->mat[i])
	{
		ft_printf("cmd: %s\n", shell->mat[i]);
		i++;	
	} */
	//free_all(); //cmd e shell
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
		//exit_error
		exit(1);
	while(i < n)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
			//exit_error
			exit(1);
		i++;
	}
	shell->max = n;
}

void	set_shell(t_shell *shell, char **envp)
{
	init_env(shell, envp);
	shell->cmds = NULL;
	shell->piper->n_pipes = 0;
	shell->piper->fds = ft_calloc(0, sizeof(int [2]));
	if (!shell->piper->fds)
		//exit_error
		exit(1);
	shell->piper->pids = ft_calloc(0, sizeof(pid_t));
	if (!shell->piper->pids)
		//exit_error
		exit(1);
}
