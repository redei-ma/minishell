/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/25 20:33:13 by redei-ma         ###   ########.fr       */
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
	int		n_pids;
	int		(*fds)[2];
	int		n_pipes;
}	t_pipex;

typedef struct s_cmd
{
	char			*cmd;
	char			**args;
	int				file_i;
	int				file_o;
	int				file_a;
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	*cmds;
	t_cmd	*head;
	t_pipex	*piper;
	char	**env;
	int		max;
	char	*input;
	char	**tokens;
	char	**heredocs;
	int		num_heredoc;
	int		signal;
}	t_shell;

extern int	g_exit_status;

// setting.c
void	set_shell(t_shell *shell);
void	loop_line(t_shell *shell);
void	init_env(t_shell *shell, char **envp);

// parsing_1.c
void	remove_spaces(char **input, int *i, char c, t_shell *shell);
void	remove_spaces_special_chars(char **input, t_shell *shell);
void	in_quotes(char **input, t_shell *shell);
void	find_unclosed_pipe(char **input, int *i, t_shell *shell);
void	find_unclosed_quotes(char **input, int *i, t_shell *shell);
void	check_unclosed(char **input, t_shell *shell);

// parsing_2.c
void	copy_special_block(char **input, char *spaced, int *i, int *j);
void	update_quotes(char c, int *in_single_quote, int *in_double_quote);
int		count_spec_char(char *input);
// void	set_var(t_shell *shell, char *input, char *format, ...);
void	set_spaces(char **input, t_shell *shell);

// parsing_3.c
void	remove_quotes(char **str, t_shell *shell);
void	delete_quotes(t_cmd *cmds, t_shell *shell);

// ft_minisplit.c
char	**ft_minisplit(char const *s);

// lst_cmd_1.c
int	fileout_manager(t_shell *shell, char **tokens, int *i);
int	filein_manager(t_shell *shell, char **tokens, int *i);
int	pipe_manager(t_shell *shell, char **tokens, int *i);
t_cmd	*ft_newcmd(t_shell *shell);
int	parse_cmds(char **tokens, t_shell *shell);

// lst_cmd_2.c
int		handle_fdout(char *token, char c, t_shell *shell);
int		handle_fdin(char *token, t_shell *shell);
char	*search_name(t_shell *shell);
int		process_heredoc_line(int fd, char *limiter);
int		handle_heredoc(char *token, t_shell *shell);

// lst_cmd_3.c
void	add_arg(char ***args, char *token, t_shell *shell);

// manager_1.c
void	exe_builtin(t_shell *shell);
void	cmd_find_son(t_shell *shell, char *cmd);
void	fork_manger(t_shell *shell);
void	cmd_find_dad(t_shell *shell, char *cmd);
void	cmd_manage(t_shell *shell);

// manager_2.c
void	ft_exit(t_shell *shell, char **args);
void	ft_env(t_shell *shell);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell);
void	ft_cd(char **string, t_shell *shell);

// ft_exec.c
void	ft_exec(t_shell *shell);

// find.c
int		is_env(char *cmd);
int		is_builtin(char *cmd);

// ft_echo_1.c
int		handle_variable(char *str, int i, t_shell *shell);
int		handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int		str_vars(char *str, t_shell *shell);
int		cmp_echo_flag(char *str);
void	ft_echo(t_shell *shell);

// ft_echo_2.c
void	write_to_fd(t_shell *shell, const char *str, int len);
char	*ft_getenv(char *nm_var, t_shell *shell);
int		handle_env_variable(char *str, int i, t_shell *shell);
int		handle_exit_status(t_shell *shell);

// ft_export.c
void	ft_printfd_shell(t_shell *shell, const char *format, char *args);
int		find_eq_sn(char *str);
int		srcd_env(t_shell *shell, const char *name);
void	ft_export(t_shell *shell, char **args);

// utils.c
char	*test_path(char **cmd_path, char *cmd, int j);
char	*find_command_path(char *path, char *cmd);
char	*get_path(char *cmd, char **envp);
int		ft_cmd_size(t_cmd *lst);
int		is_empty(char *str);

// error.c
void	free_all_2(t_shell *shell);
void	free_all(t_shell *shell);
void	delete_heredoc(t_shell *shell);
void	close_all(t_shell *shell);
int		return_partial(char *msg, t_shell *shell, int status);
void	exit_partial(char *msg, t_shell *shell, int status);
void	exit_all(char *msg, t_shell *shell, int status);

// signal.c
void	handle_ctrl_c(int signum);
void	handle_ctrl_bl(int signum);
void	interactive_ctrls(void);
void	ni_ctrls(void);
void	handle_ctrl_c_exec(int signum);

#endif