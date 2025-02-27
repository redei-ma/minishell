#ifndef MINISHELL_H
# define MINISHELL_H

# include <readline/readline.h>
# include <readline/history.h>
#include <sys/stat.h>
//# include "libft.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_shell
{
    char    *input;
    char    **cmd;
    int     i;
}   t_shell;

#endif