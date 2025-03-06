/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <lacerbi@student.42firenze.it>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/06 16:22:30 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>

/* typedef struct s_flags
{
	int	builtin;
	int	exe;
	int	redir;
	int	qutes;
	int	pipe;
	int	env;
	int	exit_status;
}	t_flags; */

typedef struct	s_env
{
	int		max;
	char	**env;
}	t_env;

typedef struct s_shell
{
	char	*input;
	char	**cmd;
}   t_shell;

int		is_empty(char *str);

#endif