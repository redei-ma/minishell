/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:39:04 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/11 14:31:27 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c_exec(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = signum;
}

void	handle_ctrl_c(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = signum;
}

void	handle_ctrl_c_get(int signum)
{
	(void)signum;
	// write(1, "\n", 1);
	g_exit_status = 130;
	// close(0);
}

void	handle_ctrl_bl(int signum)
{
	(void)signum;
}

void	interactive_ctrls(void)
{
	struct sigaction	sa_int;
	struct sigaction	sa_quit;

	sa_int.sa_handler = handle_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);
	sa_quit.sa_handler = handle_ctrl_bl;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	ni_ctrls(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bl);
}
