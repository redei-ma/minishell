/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/22 19:50:33 by renato           ###   ########.fr       */
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
	t_cmd	*cmds;
	t_pipex	*piper;
	char	**env;
	int 	max;
}	t_shell;

// setting.c
void	loop_line(t_shell *shell);
void	init_env(t_shell *shell, char **envp);
void	set_shell(t_shell *shell, char **envp);

// parsing_1.c
void	in_quotes(char **input);
void	find_unclosed_pipe(char **input, int *i);
void	find_unclosed_quotes(char **input, int *i);
void	check_unclosed(char **input);

// parsing_2.c
void	copy_special_block(char **input, char *spaced, int *i, int *j);
void	update_quotes(char c, int *in_single_quote, int *in_double_quote);
int		count_spec_char(char *input);
void	set_var(char *input, char *format, ...);
void	set_spaces(char **input);

// parsing_3.c
void	remove_quotes(char **str);
void	delete_quotes(t_cmd *cmds);

// ft_minisplit.c
char	**ft_minisplit(char const *s);

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

// manager_1.c
void	ft_cd(char **string);
void	exe_builtin(t_shell *shell);
void	fork_manger(t_shell *shell);
void	cmd_find(t_shell *shell, char *cmd);
void	cmd_manage(t_shell *shell);

// manager_2.c
void	ft_exit(t_shell *shell, char **args);
void	ft_env(t_shell *shell);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(void);

// find.c
int		is_env(char *cmd);
int		is_builtin(char *cmd);

// ft_echo_1.c
int		handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int		str_vars(char *str, t_shell *shell);
int		cmp_echo_flag(char *str);
void	ft_echo(t_shell *shell);

// ft_echo_2.c
char	*ft_getenv(char *nm_var, t_shell *shell);
int		handle_env_variable(char *str, int i, t_shell *shell);
int		handle_exit_status(t_shell *shell);
int		handle_variable(char *str, int i, t_shell *shell);

// ft_export.c
int		find_eq_sn(char *str);
int		srcd_env(t_shell *shell, const char *name);
void	ft_export(t_shell *shell, char **args);

// utils.c
void	close_all(t_shell *shell);
void	free_all(t_shell *shell);
int		ft_cmd_size(t_cmd *lst);
int		is_empty(char *str);

#endif