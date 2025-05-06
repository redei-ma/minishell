/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/02 18:11:00 by redei-ma          #+#    #+#             */
/*   Updated: 2025/05/06 15:07:53 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
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
	PIPE,		// '|'
	REDIR_IN,	// '<' or '<<'
	REDIR_OUT,	// '>' or '>>'
	WORD,		// command or argument
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
	int		*tok_type;		// enum of tokens
	char	**heredocs;		// heredocs list
	int		num_heredoc;	// number of heredocs
	int		trigger;		// error trigger
	int		exit_status;	// single quote flag
}	t_shell;

extern int	g_signal;

/*								PARSING										*/
int		check_unclosed(char **input, t_shell *shell);
int		check_syntax_error(char *input, t_shell *shell);
int		check_syntax_pipe(char *input, t_shell *shell);
void	set_spaces(char **input, t_shell *shell);
void	delete_quotes(char ***tokens, t_shell *shell);
void	remove_quotes(char **str);
void	tokenizator(t_shell *shell);
char	**ft_minisplit(char const *s);

/*								INTERPRETER									*/
void	expand_vars(t_shell *shell);
void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell);
void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str);
char	*handle_env_variable(char *str, int *i, t_shell *shell, int *new_len);
char	*expander_hd(char *str, t_shell *shell);
void	create_cmds(char **tokens, t_shell *shell);
t_cmd	*ft_newcmd(t_shell *shell);
void	pipe_manager(t_shell *shell, char **tokens, int *i);
void	filein_manager(t_shell *shell, char **tokens, int *i);
int		handle_fdin(char *token, t_shell *shell);
void	fileout_manager(t_shell *shell, char **tokens, int *i);
int		handle_heredoc(char *token, t_shell *shell);

/*								EXECUTOR									*/
void	cmd_manage(t_shell *shell);
void	cmd_find_dad(t_shell *shell, char *cmd);
void	ft_exit(t_shell *shell, char **args);
void	ft_env(t_shell *shell);
void	ft_unset(t_shell *shell, char **args);
void	ft_pwd(t_shell *shell);
void	ft_cd(char **string, t_shell *shell);
void	ft_echo(t_shell *shell);
void	ft_exec(t_shell *shell);
char	*get_path(char *cmd, char **envp);
void	ft_export(t_shell *shell, char **args);
void	process_export_arg(t_shell *shell, char *arg);
int		is_valid_identifier(char *str);
int		find_eq_sn(char *str);
void	upd_var(t_shell *shell, char *nm_var, char *var_val, int eqp);

/*								UTILS										*/
// error_1.c
void	delete_heredoc(t_shell *shell);
void	close_all(t_shell *shell);
int		return_partial(char *msg, t_shell *shell, int stat);
void	exit_all(char *msg, t_shell *shell, int stat);
// error_2.c
void	free_part(t_shell *shell);
void	free_all(t_shell *shell);
// signal_1.c
void	handle_ctrl_bl_exec(int signum);
void	handle_ctrl_bl(int signum);
void	interactive_ctrls(void);
void	ni_ctrls(void);
// signal_2.c
void	handle_ctrl_c_exec(int signum);
void	handle_ctrl_c_get(int signum);
void	handle_ctrl_c(int signum);
// utils_1.c
char	**copy_mat(char **mat, int *max_env, t_shell *shell);
void	exe_builtin(t_shell *shell);
int		is_builtin(char *cmd);
int		is_env(char *cmd);
int		is_empty(t_shell *shell);
// utils_2.c
void	ft_printfd_shell(t_shell *shell, const char *format, char *args);
void	write_to_fd(t_shell *shell, const char *str, int len);
int		srcd_env(t_shell *shell, const char *name);
int		handle_quotes(char c, int *in_single_quote, int *in_double_quote);
int		skip_space(char *input);
// utils_3.c
int		ft_wifexit(void);
int		ft_cmd_size(t_cmd *lst);

#endif
