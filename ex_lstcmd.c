/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lstcmd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 10:50:54 by redei-ma          #+#    #+#             */
/*   Updated: 2025/03/13 17:12:49 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	handle_heredoc(char *token)
{
	int		fd;
	char	*line;
	char	*limiter;

	limiter = ft_strjoin(token, "\n");
	
	fd = open("heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
	{
		//exit_error();
		exit(1);
	}
	while (1)
	{
		ft_printfd(1, "> ");
		line = get_next_line(0);
		if (!line)
			break ;
		if (!ft_strncmp(line, token, ft_strlen(token)))
		{
			free(line);
			break ;
		}
		ft_printfd(fd, "%s\n", line);
		free(line);
	}
	close(fd);
	fd = open("heredoc", O_RDONLY);
	if (fd < 0)
	{
		//exit_error();
		exit(1);
	}
	return (fd);
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


t_cmd	*parse_cmds(char **tokens, t_shell *shell)
{
	t_cmd	*head = NULL;
	t_cmd	*current = NULL;
	int		i;

	i = 0;
	current = ft_newcmd();
	if (!current)
		//exit_error();
		exit();
	head = current;
	while (tokens[i])
	{
		if (tokens[i][0] == '|' && tokens[i][1] == '\0') // Nuovo comando
		{
			shell->tot_pipe++;
			current->next = ft_newcmd();
			if (!current->next)
				//exit_error();
				exit();
			current = current->next;
		}
		else if (tokens[i][0] == '<' && tokens[i][1] == '<')
			if (tokens[++i])
				//exit_error();
				exit(1);
			current->file_i = handle_heredoc(tokens[i]);
		else if (tokens[i][0] == '<')
			if (tokens[++i])
				//exit_error();
				exit(1);
			current->file_i = handle_fdin(tokens[i]);
		else if (tokens[i][0] == '>' && tokens[i][1] == '>')
			if (tokens[++i])
			//exit_error();
				exit(1);
			current->file_a = handle_fdout(tokens[i], 'a');
		else if (tokens[i][0] == '>')
			if (tokens[++i])
				//exit_error();
				exit(1);
			current->file_o = handle_fdout(tokens[i], 'o');
		else if (!current->cmd)
			current->cmd = ft_strdup(tokens[i]);
		else
			current->args = add_arg(current->args, tokens[i]);
		i++;
	}
	return (head);
}
