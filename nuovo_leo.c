#include "minishell.h"
#include <string.h>

char *expander(char *str, t_shell *shell)
{
	int		i;
	int		j;
	int		in_single;
	int		in_double;
	char 	*expanded;

	i = 0;
	j = 0;
	in_single = 0;
	in_double = 0;
	expanded = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '\'' && !in_double)
		{
			in_single = !in_single;
			i++;
			continue;
		}
		if (str[i] == '\"' && !in_single)
		{
			in_double = !in_double;
			i++;
			continue;
		}
		if (str[i] == '$' && !in_single)
		{
			if (str[i+1] == '?')
			{
				char *status = ft_itoa(g_exit_status);
				if (!status)
				{
					free(expanded);
					exit_all("Error: malloc failed\n", shell, 1);
				}
				ft_strlcpy(expanded+j, status, ft_strlen(status)+1);
				j += ft_strlen(status);
				i += 2;
				free(status);
			}
			else if (ft_isalnum(str[i+1]) || str[i+1] == '_')
			{
				char *var = handle_env_variable(str, &i, shell);
				if (var)
				{
					ft_strlcpy(expanded+j, var, ft_strlen(var)+1);
					j += ft_strlen(var);
					free(var);
				}
				else
				{
					free(expanded);	
					exit_all("Error: malloc failed\n", shell, 1);
				}
			}
			else
				expanded[j++] = str[i++];
		}
		else
			expanded[j++] = str[i++];
	}
	if (expanded[0] == '\0')
	{
		free(expanded);
		expanded = NULL;
	}
	return (expanded);
}

void	expand_vars(t_shell *shell)
{
	int		i;
	t_cmd	*current;

	current = shell->cmds;
	while (current)
	{
		current->cmd = expander(current->cmd, shell);
		if (current->args)
		{
			i = 0;
			while (current->args[i])
			{
				current->args[i] = expander(current->args[i], shell);
				i++;
			}
		}
		current = current->next;
	}
}

char	*handle_env_variable(char *str, int *i, t_shell *shell)
{
	int			ncv;
	char		*nm_var;
	char		*var_val;

	ncv = *(i) + 1;
	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = ft_calloc((ncv - (*(i) + 1)) + 1, sizeof(char));
	if (!nm_var)
		return (NULL);
	ft_strlcpy(nm_var, &str[*(i) + 1], ncv - *(i));
	var_val = ft_getenv(nm_var, shell);
	free(nm_var);
	*(i) = ncv;
	if (var_val)
		return (ft_strdup(var_val));
	else
		return (ft_strdup(""));
}
