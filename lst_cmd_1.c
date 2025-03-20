/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_cmd_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:50:54 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/20 01:12:53 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	add_arg(char **args, char *token)
{
	char	*tmp;
	// qui e sbagliat se non ce arg devo fare il puntatore di puntatori 
	// e settarlo tutti poi usare realloc + 1 ogni altr avolta
	if (!args)
		*args = ft_strdup("");
	if (!*args)
		//exit_error();
		exit(1);
	tmp = *args;
	free(*args);
	*args = ft_strjoin(tmp, token);
	if (!*args)
		//exit_error();
		exit(1);
	free(tmp);
}

char	*search_name(void)
{
	int		n;
	char	*num;
	char	*filename;

	n = 0;
	while (1)
	{
		num = ft_itoa(n);
		if (!num)
			//exit_error();
			exit(1);
		filename = ft_strjoin("heredoc_", ft_itoa(n));
		free(num);
		if (!filename)
			//exit_error();
			exit(1);
		if (!access(filename, F_OK))
			break ;
		free(filename);
		n++;
	}
	return (filename);
}


int	handle_heredoc(char *token)
{
	int		fd;
	char	*line;
	char	*filename;

	filename = search_name();
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		//exit_error();
		exit(1);
	while (1)
	{
		ft_printfd(1, "> ");
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, token, ft_strlen(token)) && line[ft_strlen(line)] == '\n')
		{
			free(line);
			break ;
		}
		ft_printfd(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	return (handle_fdin("heredoc"));
}

int	handle_fdin(char *token)
{
	int	fd;

	fd = open(token, O_RDONLY);
	if (fd < 0)
	{
		//exit_error(); devo settare bene erno per file non esistente
		exit(1);
	}
	return (fd);
}

int	handle_fdout(char *token, char c)
{
	int	fd;

	if (c == 'o')
		fd = open(token, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (c == 'a')
		fd = open(token, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd < 0)
	{
		//exit_error();
		exit(1);
	}
	return (fd);
}

t_cmd	*ft_newcmd(void)
{
	t_cmd	*new;

	new = malloc(sizeof(t_cmd));
	if (!new)
		//exit_errror();
		exit(1);
	new->cmd = NULL;
	new->args = NULL;
	new->file_i = -1;
	new->file_o = -1;
	new->file_a = -1;
	new->next = NULL;
	return (new);
}


void	parse_cmds(char **tokens, t_shell *shell)
{
	t_cmd	*head;
	int		i;

	i = 0;
	shell->cmds = ft_newcmd();
	if (!shell->cmds)
		//exit_error();
		exit(1);
	head = shell->cmds;
	while (tokens[i])
	{
		if (tokens[i][0] == '|') // Nuovo comando
			pipe_manager(shell, tokens, &i);
		else if (tokens[i][0] == '<')
			filein_manager(shell, tokens, &i);
		else if (tokens[i][0] == '>')
			fileout_manager(shell, tokens, &i);
		else if (!shell->cmds->cmd)
			shell->cmds->cmd = ft_strdup(tokens[i]);
		else
			add_arg(shell->cmds->args, tokens[i]);
		if (!tokens[++i])
			break ;
	}
	shell->cmds = head;
}
