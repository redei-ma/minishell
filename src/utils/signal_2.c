/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:29:45 by renato            #+#    #+#             */
/*   Updated: 2025/04/29 19:33:21 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_ctrl_c_exec(int signum)
{
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	ft_printfd(2, "no redisplay\n");
	ft_printfd(2, "no redisplay\n");
	ft_printfd(2, "no redisplay\n");
	ft_printfd(2, "no redisplay\n");
	g_signal = signum;
}

void	handle_ctrl_c(int signum)
{
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	ft_printfd(2, "redisplay\n");
	g_signal = signum;
}

void handle_ctrl_c_get(int signum)
{
    (void)signum;
    g_signal = 130;
    // rl_replace_line("", 0);
    // rl_done = 1;
    rl_on_new_line();
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
}
