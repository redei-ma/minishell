/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/04/14 15:36:18 by redei-ma         ###   ########.fr       */
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
# include <errno.h>
# include <sys/ioctl.h>
# include <termios.h> 

enum e_token
{
	PIPE = 124,			// '|'
	REDIR_IN = 60,		// '<'
	HEREDOC = 257,		// '<<'
	REDIR_OUT = 62,		// '>'
	REDIR_APPEND = 256,	// '>>'
	WORD = 258,			// other
};

typedef struct s_pipex
{
	pid_t	*pids;		// array of process ids
	int		n_pids;		// number of processes
	int		(*fds)[2];	// array of pipes
	int		n_pipes;	// number of pipes
}	t_pipex;

typedef struct s_cmd
{
	int				type;		// enum e_token
	char			*cmd;		// name_command
	char			**args;		// arguments_command
	int				file_i;		// file_in
	int				file_o;		// file_out
	int				file_a;		// file_append
	int				skip;		// flag
	struct s_cmd	*next;
}	t_cmd;

typedef struct s_shell
{
	t_cmd	*cmds;			// list of commands
	t_cmd	*head;			// head of commands list
	t_pipex	*piper;			// pipex struct
	char	**env;			// minishell variables
	int		max;			// size of env
	char	*input;			// readline input
	char	**tokens;		// tokens of input
	char	**heredocs;		// heredocs list
	int		num_heredoc;	// number of heredocs
	int		trigger;		// error trigger
}	t_shell;

extern int	g_exit_status;

// main.c
void	set_shell(t_shell *shell);
void	loop_line(t_shell *shell);

// parsing_1.c
void	in_quotes(char **input, t_shell *shell);
void	find_unclosed_pipe(char **input, int *i, t_shell *shell);
void	find_unclosed_quotes(char **input, int *i, t_shell *shell);
void	check_unclosed(char **input, t_shell *shell);

// parsing_2.c
void	copy_special_block(char **input, char *spaced, int *i, int *j);
void	update_quotes(char c, int *in_single_quote, int *in_double_quote);
int		count_spec_char(char *input);
void	set_spaces(char **input, t_shell *shell);

// parsing_3.c
void	remove_quotes(char **str);
void	delete_quotes(char ***tokens, t_shell *shell);
int		check_syntax(char *input, char c, t_shell *shell);
int		check_syntax_pipe(char *input, t_shell *shell);
void	check_syntax_error(char *input, t_shell *shell);

// ft_minisplit.c
char	**ft_minisplit(char const *s);

// lst_cmd_1.c
void	fileout_manager(t_shell *shell, char **tokens, int *i);
void	filein_manager(t_shell *shell, char **tokens, int *i);
void	pipe_manager(t_shell *shell, char **tokens, int *i);
t_cmd	*ft_newcmd(t_shell *shell);
void	is_valid_env(char **tokens, int i, t_shell *shell);
void	parse_cmd(char **tokens, t_shell *shell);
void	create_cmds(char **tokens, t_shell *shell);

// lst_cmd_2.c
int		handle_fdout(char *token, char c, t_shell *shell);
int		handle_fdin(char *token, t_shell *shell);
char	*search_name(t_shell *shell);
int		process_heredoc_line(int *fd, char *key, t_shell *shell);
int		handle_heredoc(char *token, t_shell *shell);

// lst_cmd_3.c
void	add_arg(char ***args, char *token, t_shell *shell);

// expander_1.c
void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell);
void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str);
void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str);
char	*expander(char *str, t_shell *shell, int qts_yon);
void	expand_vars(char ***tokens, t_shell *shell);
char	*handle_env_variable(char *str, int *i, t_shell *shell);
char	*ft_getenv(char *nm_var, t_shell *shell);
int		handle_exit_status(t_shell *shell);

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

// ft_echo_1.c
int		handle_quotes(char c, int *in_single_quote, int *in_double_quote);
void	write_to_fd(t_shell *shell, const char *str, int len);
int		str_vars(char *str, t_shell *shell);
void	ft_echo(t_shell *shell);

// ft_export_1.c
int		find_eq_sn(char *str);
void	sort_env(char **env);
void	print_env_var(t_shell *shell, char *env_var);
void	print_env_declare(t_shell *shell);
int		handle_export_value(t_shell *shell, char *arg, int eq_pos);
void	process_export_arg(t_shell *shell, char *arg);
void	ft_export(t_shell *shell, char **args);

// ft_export_2.c
char	*var_creation(const char *nm_var, const char *var_val, int eqp);
int		srcd_env(t_shell *shell, const char *name);
int		update_existing_var(t_shell *shell, int index, char *n_full_var);
int		create_new_env_array(t_shell *shell, char *n_full_var);
void	upd_var(t_shell *shell, const char *nm_var,
			const char *var_val, int eqp);

// ft_exec_1.c
char	*get_path(char *cmd, char **envp);
char	**ft_cmd_join(char *cmd, char **args, t_shell *shell);
void	set_dups(t_cmd *cmd, t_shell *shell);
void	ft_exec(t_shell *shell);

// ft_exec_2.c
char	*test_path(char **cmd_path, char *cmd, int j);
char	*find_command_path(char *path, char *cmd);

// utils.c
int		skip_space(char *input);
char	**copy_mat(char **mat, int *max_env, t_shell *shell);
void	ft_printfd_shell(t_shell *shell, const char *format, char *args);
int		is_env(char *cmd);
int		is_builtin(char *cmd);
int		ft_cmd_size(t_cmd *lst);
int		is_empty(char *str);

// error.c
void	free_part_2(t_shell *shell);
void	free_part(t_shell *shell);
void	free_all(t_shell *shell);
void	delete_heredoc(t_shell *shell);
void	close_all(t_shell *shell);
int		return_partial(char *msg, t_shell *shell, int status);
void	exit_partial(char *msg, t_shell *shell, int status);
void	exit_all(char *msg, t_shell *shell, int status);

// signal.c
void	handle_ctrl_c_exec(int signum);
void	handle_ctrl_c(int signum);
void	handle_ctrl_c_get(int signum);
void	handle_ctrl_bl(int signum);
void	interactive_ctrls(void);
void	ni_ctrls(void);

#endif