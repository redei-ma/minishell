/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 15:11:42 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/02 17:50:02 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_pipex
{
	int		ac;
	char	**av;
	char	**envp;
	pid_t	*pids;
	int		n_cmds;
	int		**fds;
	int		n_pipes;
	int		i;
	int		flag;
}	t_pipex;

char	*already_path(char *cmd);
void	execute(t_pipex **piper, char *av, char **envp);
void	last_process(t_pipex **piper, int *fd);
void	first_process(t_pipex **piper, int *fd);
void	run(t_pipex **piper);

char	*test_path(char **cmd_path, char *cmd, int j);
char	*find_command_path(char *path, char *cmd);
char	*get_path(char *cmd, char **envp);
void	set_pipe(t_pipex **piper);
void	set_piper(t_pipex **piper, int ac, char **av, char **envp);

void	free_all(char **mat, char *str);
void	exit_error(char *msg, t_pipex **piper, char **cmd, char *path);
void	safe_close(int fd);
void	close_all(int fd1, int fd2);
void	close_pipes(int **fds, int size);

#endif