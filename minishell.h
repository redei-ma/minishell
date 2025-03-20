/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/20 00:48:31 by renato           ###   ########.fr       */
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

typedef struct s_pipex
{
	pid_t	*pids;
	int		(*fds)[2];
	int		n_pipes;
	// int		i;
	// int		flag;
}	t_pipex;

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
	// char	*input;
	// char	**mat;
	t_cmd	*cmds;
	t_pipex	*piper;
	char	**env;
	int 	max;
	// int		tot_pipe;
}	t_shell;

/* Functions */
int		count_spec_char(char *input);
void	set_var(char *input, char *format, ...);
void	copy_special_block(char **input, char *spaced, int *i, int *j);
void	update_quotes(char c, int *in_single_quote, int *in_double_quote);
void	set_spaces(char **input);
void	loop_line(t_shell *shell);
void	set_shell(t_shell *shell, char **envp);
void	parse_cmds(char **tokens, t_shell *shell);
void	add_arg(char **args, char *token);
char	*search_name(void);
int		handle_heredoc(char *token);
int		handle_fdin(char *token);
int		handle_fdout(char *token, char c);
t_cmd	*ft_newcmd(void);
void	pipe_manager(t_shell *shell, char **tokens, int *i);
void	filein_manager(t_shell *shell, char **tokens, int *i);
void	fileout_manager(t_shell *shell, char **tokens, int *i);

void	init_env(t_shell *shell, char **envp);

int		is_empty(char *str);
char	**ft_minisplit(char const *s);

#endif