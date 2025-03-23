/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/23 03:13:29 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int exit_status = 0;

int	main(int ac, char **av, char **envp)
{
	t_shell	*shell;

	(void )av;
	if (ac != 1)
		return (ft_printfd(2, "Error: too many arguments\n"), 1);
	shell = ft_calloc(1, sizeof(t_shell));
	if (!shell)
		return (ft_printf("Error: malloc failed"), 1);
	shell->piper = ft_calloc(1, sizeof(t_pipex));
	if (!shell->piper)
		return (free(shell), ft_printfd(2, "Error, Malloc faild"), 1);
	set_shell(shell, envp);
	while (1)
		loop_line(shell);
	// loop_line(shell);
	return (0);
}
