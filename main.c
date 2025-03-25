/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/25 16:42:47 by redei-ma         ###   ########.fr       */
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
	init_env(shell, envp);
	shell->signal = 0;
	while (1)
		loop_line(shell);
	// loop_line(shell);
	exit_all("Si e chiuso il programma", shell, 0); //da togliere
}
