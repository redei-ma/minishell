/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lacerbi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:17:37 by lacerbi           #+#    #+#             */
/*   Updated: 2025/03/05 18:02:23 by lacerbi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int	valid_name(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (-1);
	i++;
	while (name[i] != '\0')
		if (name[0] != '_') || !ft_isalnum(name[i]))
			return (-1);
	return (0);
}

typedef struct	s_env
{
	int	max;
	char	**env;
}	t_env;

int	find_eq_sn(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void	init_env(t_env *e, char **envp)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (envp[n])
		n++;
	e->env = malloc(sizeof(char *) * (n + 1));
	if (!e->env)
		exit(1);
	while(i < n)
	{
		e->env[i] = ft_strdup(envp[i]);
		i++;
	}
	e->max = n;
	e->env[n] = NULL;
}

int	srcd_env(t_env *e, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (e->env[i])
	{
		if (ft_strncmp(e->env[i], name, len) == 0 && e->env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*var_creation(const char *nm_var, const char *var_val)
{
	char	*temp;
	char	*n_full_var;

	temp = ft_strjoin(nm_var, "=");
	if (!temp)
		return (NULL);

	n_full_var = ft_strjoin(temp, var_val);
	free(temp);

	return (n_full_var);
}

void	upd_var(t_env *e, const char *nm_var, const char *var_val)
{
	int	index;
	int	i;
	char	*n_full_var;
	char	**new_env;

	i = -1;
	index = srcd_env(e, nm_var);
	n_full_var = var_creation(nm_var, var_val);
	if (!n_full_var)
		return ;
	if (index != -1)
	{
		free(e->env[index]);
		e->env[index] = n_full_var;
	}
	else
	{
		new_env = malloc(sizeof(char *) * (e->max + 2));
		if (!new_env)
		{
			free(n_full_var);
			return ;
		}
		while (++i < e->max)
			new_env[i] = e->env[i];
		new_env[i] = n_full_var;
		new_env[i + 1] = NULL;
		free(e->env);
		e->env = new_env;
		e->max++;
	}
}

int	ft_export(t_env *e, char **args)
{
	int		i;
	int		eqp;
	char		*name;
	char		*val;

	if (!args[0])
	{
		i = 0;
		while (e->env[i])
		{
			ft_printf("declare -x %s\n", e->env[i]);
			i++;
		}
		return (0);
	}
	i = 0;
	while (args[i])
	{
		eqp = find_eq_sn(args[i]);
		if (eqp != -1)
		{
			name = ft_substr(args[i], 0, eqp);
			if (!name)
				return (1);
			val = ft_substr(args[i], eqp + 1, ft_strlen(args[i]) - eqp - 1);
			if (!val)
			{
				free(name);
				return (1);
			}
			upd_var(e, name, val);
			free(name);
			free(val);
		}
		else
			upd_var(e, args[i], "");
		i++;
	}
	return (0);
}


int	ft_pwd()
{
	char	cwd[1024];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (-1);
	}
	return (0);
}

int	ft_cd(char *string)
{
	if (ft_strlen(string) == 0)
	{
		write(2, "cd: comando non valido!", 23);
		return (-1);
	}
	if (chdir(string) != 0)
	{
		perror("cd");
		return (-1);
	}
	return (0);
}

int	ft_echo(char *string, int flag, int fd)
{
	write(fd, string, ft_strlen(string));
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}
