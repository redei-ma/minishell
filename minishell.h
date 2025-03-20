/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/20 21:40:17 by renato           ###   ########.fr       */
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

// setting.c
void	loop_line(t_shell *shell);
void	init_env(t_shell *shell, char **envp);
void	set_shell(t_shell *shell, char **envp);

// parsing_1.c
void	in_quotes(char **input);
void	check_open_quotes(char **input);

// parsing_2.c
void	copy_special_block(char **input, char *spaced, int *i, int *j);
void	update_quotes(char c, int *in_single_quote, int *in_double_quote);
int		count_spec_char(char *input);
void	set_var(char *input, char *format, ...);
void	set_spaces(char **input);

// parsing_3.c
void	remove_quotes(char **str);
void	delete_quotes(t_cmd *cmds);

// lst_cmd_1.c
void	fileout_manager(t_shell *shell, char **tokens, int *i);
void	filein_manager(t_shell *shell, char **tokens, int *i);
void	pipe_manager(t_shell *shell, char **tokens, int *i);
t_cmd	*ft_newcmd(void);
void	parse_cmds(char **tokens, t_shell *shell);

// lst_cmd_2.c
int		handle_fdout(char *token, char c);
int		handle_fdin(char *token);
char	*search_name(void);
int		process_heredoc_line(int fd, char *limiter);
int		handle_heredoc(char *token);

// lst_cmd_3.c
void	add_arg(char ***args, char *token);

// ft_minisolit.c
char	**ft_minisplit(char const *s);

// utils.c
int		is_empty(char *str);

#endif