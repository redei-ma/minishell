#include "minishell.h"
#include <stddef.h>

char *expander(char *str, t_shell *shell, int qts_yon)
{
	int	len = ft_strlen(str);
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
		if (qts_yon != 1 && handle_quotes(str[i], &in_single, &in_double))
		{
			expanded[j++] = str[i++];
			continue;
		}
		if (str[i] == '$' && !in_single)
		{
			if (str[i + 1] == '?')
			{
				char *status = ft_itoa(g_exit_status);
				if (!status)
				{
					free(expanded);
					exit_all("Error: malloc failed\n", shell, 1);
				}
				expanded = ft_realloc(expanded, (len + 1) * sizeof(char), (len + ft_strlen(status) - 2 + 1) * sizeof(char));
				if (!expanded)
				{
					free(status);
					exit_all("Error: malloc failed\n", shell, 1);
				}
				ft_strlcpy(expanded + j, status, ft_strlen(status) + 1);
				j += ft_strlen(status);
				i += 2;
				len += ft_strlen(status) - 2;
				free(status);
			}
			else if (ft_isalnum(str[i+1]) || str[i+1] == '_')
			{
				int x = i;
				char *var = handle_env_variable(str, &i, shell);
				if (!var)
				{
					free(expanded);
					exit_all("Error: malloc failed\n", shell, 1);
				}
				expanded = ft_realloc(expanded, (len + 1) * sizeof(char), (len + ft_strlen(var) - (i - x)  + 1) * sizeof(char)); //manca quanto misura la var dopo dollaro
				if (!expanded)
				{
					free(var);
					exit_all("Error: malloc failed\n", shell, 1);
				}
				ft_strlcpy(expanded+j, var, ft_strlen(var)+1);
				j += ft_strlen(var);
				free(var);
			}
			else
				expanded[j++] = str[i++];
		}
		else
			expanded[j++] = str[i++];
	}
	free(str);
	return (expanded);
}

void	expand_vars(char ***tokens, t_shell *shell)
{
	size_t	i;
	size_t	j;

	i = 0;
	while ((*tokens)[i])
	{
		if (i > 0 && ((*tokens)[i - 1][0] == '<' && (*tokens)[i - 1][1] == '<'))
		{
			remove_quotes(&(*tokens)[i]);
			if (!(*tokens)[i])
				exit_all("Error: malloc failed\n", shell, 1);
			i++;
			continue;
		}
		(*tokens)[i] = expander((*tokens)[i], shell, 0);
		if ((*tokens)[i][0] == '\0')
		{
			free((*tokens)[i]);
			j = i;
			while ((*tokens)[j])
			{
				(*tokens)[j] = (*tokens)[j + 1];
				j++;
			}
			(*tokens)[j] = NULL;
			i--;
		}
		i++;
	}
}

char	*handle_env_variable(char *str, int *i, t_shell *shell)
{
	int			ncv;
	char		*nm_var;
	char		*var_val;

	ncv = *i + 1;
	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = ft_calloc((ncv - (*i + 1)) + 1, sizeof(char));
	if (!nm_var)
		return (NULL);
	ft_strlcpy(nm_var, &str[*i + 1], ncv - *i);
	var_val = ft_getenv(nm_var, shell);
	free(nm_var);
	*i = ncv;
	if (var_val)
		return (ft_strdup(var_val));
	else
		return (ft_strdup(""));
}

char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int			i;
	char		*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

int	handle_exit_status(t_shell *shell)
{
	int			last_exit_status;
	char		*exit_cd;

	last_exit_status = 0;
	exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write_to_fd(shell, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}
