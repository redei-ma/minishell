/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:39:04 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/25 18:25:05 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <readline/readline.h>

void	handle_ctrl_c(int signum)
{
	(void)signum;
	if (isatty(STDIN_FILENO))
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);//cancella la riga corrente di readline
		rl_on_new_line();
		rl_cleanup_after_signal();
		rl_free_line_state();
		g_exit_status = 130;
	}
	else
	{
		close(STDIN_FILENO);//chiude l'input per interrompere potenziali read
	}
}

void	handle_ctrl_bl(int signum)
{
	(void)signum;//ignora segnale
}

void	interactive_ctrls(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;// Continua se un segnale interrompe una system call
	sigaction(SIGINT, &sa_int, NULL);//da queste modifiche a SIGINT

	sa_quit.sa_handler = handle_ctrl_bl;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);//applica la configurazione a ctrl+b
}

void	ni_ctrls(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bl);
}
