/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/12 16:02:36 by redei-ma         ###   ########.fr       */
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

typedef struct s_cmd
{
	char	*cmd;
	char	**args;
	int		file_i;
	int		file_o;
	int		file_a;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	char	*input;
	char	**mat;
	s_cmd	*cmds;
	char	**env;
	int 	max;
}	t_shell;

int		is_empty(char *str);
char	**ft_minisplit(char const *s);

#endif