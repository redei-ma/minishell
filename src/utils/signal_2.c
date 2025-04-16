/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/16 11:29:45 by renato            #+#    #+#             */
/*   Updated: 2025/04/16 11:29:59 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell."

void	handle_ctrl_c_exec(int signum)
{
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = signum;
}

void	handle_ctrl_c(int signum)
{
	write(1, "\n", 1);
	// rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_exit_status = signum;
}

void	handle_ctrl_c_get(int signum)
{
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	// rl_replace_line("", 0);
	rl_on_new_line();
	g_exit_status = signum;
}
