/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:35:37 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/20 13:05:58 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
