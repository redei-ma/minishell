/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   settings.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:07:08 by renato            #+#    #+#             */
/*   Updated: 2025/04/01 17:53:39 by lacerbi          ###   ########.fr       */
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
/*
char	*expander(char *str, t_shell *shell)
{
	int	i;
	int	j;
	int	in_single_quote;
	int	in_double_quote;
	char	*exp_var;
	char	*expanded;

	i = 0;
	j = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	expanded = malloc(ft_strlen(str) + 1);
	if (!expanded)
		return (NULL);
	while (str[i] != '\0')
	{
		if (handle_quotes(str[i], &in_single_quote, &in_double_quote))
			expanded[j++] = str[i++];
		else if (str[i] == '$' && !in_single_quote && str[i + 1] != '?')
		{
			j = i;
			exp_var = handle_env_variable(str, &i, shell);
			if (exp_var && exp_var[0] != '\0')
			{
				expanded = ft_realloc(expanded, ft_strlen(expanded)
						, ft_strlen(expanded) - (i - j) + ft_strlen(exp_var));
				i = 0;
				while (exp_var[i])
					expanded[j++] = exp_var[i++];
			}
			else
			{
				expanded = ft_realloc(expanded, ft_strlen(expanded)
						, ft_strlen(expanded) - (i - j));
				str[j++] = ' ';
			}
			i = j;
		}
		else
			expanded[j++] = str[i++];
	}
	expanded[j] = '\0';
	return (expanded);
}*/

char *expander(char *str, t_shell *shell)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	char 	*expanded;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	expanded = malloc(ft_strlen(str) + 1);
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue;
		}
		if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue;
		}
		if (str[i] == '$' && !in_single)
		{
			if (str[i+1] == '?')
			{
				char *status = ft_itoa(g_exit_status);
				ft_strlcpy(expanded+j, status, ft_strlen(status)+1);
				j += ft_strlen(status);
				i += 2;
				free(status);
			} 
			else if (ft_isalnum(str[i+1]) || str[i+1] == '_')
			{
				char *var = handle_env_variable(str, &i, shell);
				if (var)
				{
					ft_strlcpy(expanded+j, var, ft_strlen(var)+1);
					j += ft_strlen(var);
					free(var);
				}
			}
			else
			{
				expanded[j++] = str[i++];
			}
		}
		else
		{
			expanded[j++] = str[i++];
		}
	}
	expanded[j] = '\0';
	return expanded;
}

void	expand_vars(t_shell *shell)
{
	int		i;
	t_cmd	*current;

	current = shell->cmds;
	while (current)
	{
		current->cmd = expander(current->cmd, shell);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				current->args[i] = expander(current->args[i], shell);
				i++;
			}
		}
		current = current->next;
	}
}

void	loop_line(t_shell *shell)
{
	set_shell(shell);
	shell->input = readline("minishell> ");
	// shell->input = ft_strdup("ls | ");
	if (!shell->input)
		exit_all("exit", shell, 0); // capire se viene chiamato due volte o va bene e se va bene il numero di uscita o se non deve stamapre niente
	check_unclosed(&shell->input, shell);
	if (shell->input[0])
		add_history(shell->input);
	if (is_empty(shell->input))
		return ;
	set_spaces(&shell->input, shell);
	//check_syntax_error(shell->input, shell);
	if (shell->trigger)
	{
		//capire se lo esegue. su mac mi pare che se sia prima lo fa senno no
		// exec_heredoc(); // da fare
		return_partial(NULL, shell, 1);
	}
	shell->tokens = ft_minisplit(shell->input);
	if (!shell->tokens)
		exit_all("Error: malloc failed\n", shell, 1);
	create_cmds(shell->tokens, shell);
	if (shell->trigger)
	{
		rl_on_new_line(); // serve?
		return_partial(NULL, shell, 1); // errore da capire
	}
	expand_vars(shell);
	// ft_print_cmd(shell->cmds);
	delete_quotes(shell->cmds, shell);
	cmd_manage(shell);
}

