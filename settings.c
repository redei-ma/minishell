/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/03/20 17:37:55 by renato           ###   ########.fr       */
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

void	in_quotes(char **input)
{
	char	*line;
	char	*newline;
	
	ft_printfd(1, "> ");
	line = get_next_line(0);
	if (!line)
		//exit_error bash: syntax error: unexpected end of file
		exit(1);
	newline = ft_strjoin(*input, line);
	if (!newline)
	{
		free(line);
		//exit_error
		exit(1);
	}
	free(line);
	free(*input);
	*input = newline;
}


void	check_quotes(char **input)
{
	int	i;
	char	quote;
	
	i = 0;
	while ((*input)[i])
	{
		if ((*input)[i] == '\'' || (*input)[i] == '\"')
		{
			quote = (*input)[i];
			i++;
			while ((*input)[i] && (*input)[i] != quote)
				i++;
		}
		if (!(*input)[i])
		{
			i = -1;
			in_quotes(input);
		}
		i++;
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
	check_quotes(&input);
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
