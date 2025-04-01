/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/01 17:13:54 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	if (isatty(STDIN_FILENO))
		interactive_ctrls();
	else
		ni_ctrls();
	(void )av;
	if (ac != 1)
		return (ft_printfd(2, "Error: too many arguments\n"), 1);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (ft_printf("Error: malloc failed"), 1);
	shell->piper = ft_calloc(1, sizeof(t_pipex));
	if (!shell->piper)
		return (free(shell), ft_printfd(2, "Error, Malloc faild"), 1);
	shell->env = copy_mat(envp, &shell->env_max, shell);
	shell->first_env = shell->env_max;
	shell->signal = 0;
	shell->original_stdin = dup(STDIN_FILENO);
	shell->original_stdout = dup(STDOUT_FILENO);
	while (1)
		loop_line(shell);
	// loop_line(shell);
	exit_all("Si e chiuso il programma", shell, 0); //da togliere
}
