/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:29:45 by renato            #+#    #+#             */
/*   Updated: 2025/04/29 17:38:41 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c_exec(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	g_signal = signum;
}

void	handle_ctrl_c(int signum)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_signal = signum;
}

void handle_ctrl_c_get(int signum)
{
    (void)signum;
    g_signal = 130;
    rl_replace_line("", 0);
    rl_done = 1;
    rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
