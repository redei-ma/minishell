/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/20 13:01:29 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

/* void	exe_builtin(t_shell *shell)
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
} */

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

/* void	cmd_manage(t_cmd *cmds)
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
} */

int	count_spec_char(char *input)
{
	int	i;
	int	count;
	char	special;

	i = 0;
	count = 0;
	while (input[i])
	{
		if (input[i] == '|' || input[i] == '>' || input[i] == '<')
		{
			special = input[i];
			while (special == input[i] && input[i + 1] == special)
				i++;
			count += 2;
		}
		i++;
	}
	return (count + i + 1);
}

void	set_var(char *input, char *format, ...)
{
	int		i;
	char	*spaced;

	i = 0;
	spaced =  ft_calloc(count_spec_char(input), sizeof(char));
	if (!spaced)
		//exit_error();
		exit(1);
	va_list args;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '0')
			*(va_arg(args, int *)) = 0;
		else if (format[i] == '1')
			*(va_arg(args, char **)) = spaced;
		i++;
	}
	va_end(args);
}

void	copy_special_block(char **input, char *spaced, int *i, int *j)
{
	char special;

	special = (*input)[*i];
	spaced[(*j)++] = ' ';
	while ((*input)[*i] == special)
		spaced[(*j)++] = (*input)[(*i)++];
	spaced[(*j)++] = ' ';
}

void	update_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
		*in_single_quote = !(*in_single_quote);
	else if (c == '"' && !(*in_single_quote))
		*in_double_quote = !(*in_double_quote);
}

void	set_spaces(char **input)
{
	int		i;
	int		j;
	int		in_single_quote;
	int		in_double_quote;
	char	*spaced;

	set_var(*input, "00001", &i, &j, &in_single_quote, &in_double_quote, &spaced);
	while ((*input)[i])
	{
		update_quotes((*input)[i], &in_single_quote, &in_double_quote);
		if (((*input)[i] == '|' || (*input)[i] == '>' || (*input)[i] == '<') && !in_single_quote && !in_double_quote)
			copy_special_block(input, spaced, &i, &j);
		else
			spaced[j++] = (*input)[i++];
	}
	free(*input);
	*input = spaced;
}

void ft_print_cmd(t_cmd *cmds)
{
	int i = 0;
	while (cmds)
	{
		ft_printf("cmd: %s\n", cmds->cmd);
		ft_printf("args: ");
		while (cmds->args[i])
			ft_printf("%s, ", cmds->args[i++]);
		ft_printf("\n");
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

void	set_shell(t_shell *shell, char **envp)
{
	init_env(shell, envp);
	shell->cmds = NULL;
	shell->piper->n_pipes = 0;
	shell->piper->fds = NULL;
	shell->piper->pids = NULL;
}

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (ac != 1)
		return (ft_printf("minishell: too many arguments\n"));
	(void )av;
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (1);
	shell->piper = ft_calloc(1, sizeof(t_pipex));
	if (!shell->piper)
		return (free(shell), 1);
	set_shell(shell, envp);
	while (1)
		loop_line(shell);
	return 0;
}
