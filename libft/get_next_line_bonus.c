/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 16:37:58 by redei-ma          #+#    #+#             */
/*   Updated: 2025/02/24 16:49:17 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*find_newline(char **str)
{
	char	*fin;
	char	*tmp;
	int		i;

	i = 0;
	fin = NULL;
	while ((*str)[i] && (*str)[i] != '\n')
		i++;
	if ((*str)[i] == '\n')
	{
		fin = ft_substr(*str, 0, i + 1);
		if (!fin)
			return (free(*str), NULL);
		if (i == (int)ft_strlen(*str) - 1)
			tmp = NULL;
		else
		{
			tmp = ft_substr(*str, i + 1, ft_strlen(*str) - i - 1);
			if (!tmp)
				return (free(fin), free(*str), NULL);
		}
		free(*str);
		*str = tmp;
	}
	return (fin);
}

int	read_line(char **s, int fd)
{
	char	*buff;
	char	*tmp;
	ssize_t	bytes_read;

	buff = (char *)ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return (-1);
	bytes_read = read(fd, buff, BUFFER_SIZE);
	if (bytes_read > 0)
	{
		tmp = ft_strjoin(*s, buff);
		if (!tmp)
		{
			free(buff);
			return (-1);
		}
		free(*s);
		*s = tmp;
	}
	free(buff);
	return (bytes_read);
}

char	*test(char **leftovers, char **final, int bytes)
{
	if (bytes < 0)
	{
		free(*leftovers);
		*leftovers = NULL;
		return (NULL);
	}
	else if (bytes == 0)
	{
		if (*leftovers && ft_strlen(*leftovers) > 0)
		{
			*final = *leftovers;
			*leftovers = NULL;
			return (*final);
		}
		free(*leftovers);
		*leftovers = NULL;
		return (NULL);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char	*leftovers[4096];
	char		*final;
	int			bytes;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!leftovers[fd])
		leftovers[fd] = (ft_strdup(""));
	if (!leftovers[fd])
		return (NULL);
	while (1)
	{
		final = find_newline(&leftovers[fd]);
		if (final)
			return (final);
		if (!leftovers[fd])
			return (NULL);
		bytes = read_line(&leftovers[fd], fd);
		if (bytes <= 0)
			return (test(&leftovers[fd], &final, bytes));
	}
}

/*int main(int argc, char **argv)
{
    int fd1, fd2;
    char *line1, *line2;
	if (argc != 3) // Due file richiesti come input
    {
        fprintf(stderr, "Usage: %s <file1> <file2>\n", argv[0]);
        return (EXIT_FAILURE);
    }    // Apertura del primo file
    fd1 = open(argv[1], O_RDONLY);
    if (fd1 < 0)
    {
        perror("Error opening file 1");
        return (EXIT_FAILURE);
    }    // Apertura del secondo file
    fd2 = open(argv[2], O_RDONLY);
    if (fd2 < 0)
    {
        perror("Error opening file 2");
        close(fd1); // Chiude il primo file prima di uscire
        return (EXIT_FAILURE);
    }    // Leggi alternativamente dai due file
    while (1)
    {
        line1 = get_next_line(fd1);
        if (line1 != NULL)
        {
            printf("File1: %s\n", line1);
            free(line1);
        }        line2 = get_next_line(fd2);
        if (line2 != NULL)
        {
            printf("File2: %s\n", line2);
            free(line2);
        }
        if (line1 == NULL && line2 == NULL)
            break;
    }    close(fd1);
    close(fd2);
    return (EXIT_SUCCESS);
} */
