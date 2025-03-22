#include "libft/libft.h"
#include "minishell.h"

int	is_env(char *cmd)
{
	int i;

	i = 0;
	while (cmd[i] && cmd[i] != '=' && ft_isascii(cmd[i]))
		i++;
	if (cmd[i] == '=' && i > 0)
		return (1);
	return (0);
}

int	is_builtin(char *cmd)
{
	if(ft_strncmp(cmd, "echo", 4) == 0)
		return 1;
	else if(ft_strncmp(cmd, "cd", 2) == 0)
		return 1;
	else if(ft_strncmp(cmd, "pwd", 3) == 0)
		return 1;
	else if(ft_strncmp(cmd, "export", 6) == 0)
		return 1;
	else if(ft_strncmp(cmd, "unset", 5) == 0)
		return 1;
	else if(ft_strncmp(cmd, "env", 3) == 0)
		return 1;
	else if(ft_strncmp(cmd, "exit", 4) == 0)
		return 1;
	return 0;
}
