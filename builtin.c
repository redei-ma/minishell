/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: redei-ma <redei-ma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:17:37 by lacerbi           #+#    #+#             */
/*   Updated: 2025/03/12 15:35:58 by redei-ma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell *shell, char **envp)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (envp[n])
		n++;
	shell->env = ft_calloc((n + 1), sizeof(char *));
	if (!shell->env)
	{
		free(shell);
		exit(1);
	}
	while(i < n)
	{
		shell->env[i] = ft_strdup(envp[i]);
		if (!shell->env[i])
		{
			ft_freemat((void *)shell->env, i);
			free(shell);
			exit(1);
		}
		i++;
	}
	shell->max = n;
}

//------------------------------------------------------------------------------------------------

int	valid_name(char *name)
{
	int	i;

	i = 0;
	if (!name || (!ft_isalpha(name[0]) && name[0] != '_'))
		return (-1);
	i++;
	while (name[i] != '\0')
		if (name[0] != '_' || !ft_isalnum(name[i]))
			return (-1);
	return (0);
}

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
			val = NULL;
			if (name)
			    val = ft_substr(args[i], eqp + 1, ft_strlen(args[i]) - eqp - 1);
			if (!name || !val)
			{
			    free(name);
			    free(val);
			    return (1);
			}
			upd_var(e, name, val);
			free(name);
			free(val);
		}
		else if (srcd_env(e, args[i]) == -1)
			upd_var(e, args[i], "");
		i++;
	}
	return (0);
}

//------------------------------------------------------------------------------------------------

void	ft_unset(t_env *e, char **args)
{
	int	index;
	int	i;
	int	j;

	if (!args[0])
		return ;
	i = 0;
	while (args[i])
	{
		index = srcd_env(e, args[i]);
		if (index != -1)
		{
			free(e->env[index]);
			j = index;
			while (e->env[j])
			{
				e->env[j] = e->env[j + 1];
				j++;
			}
			e->max--;
		}
		i++;
	}
}

//------------------------------------------------------------------------------------------------

int	ft_env(t_env **e)
{
	int	i;

	i = 0;
	if (!e || !e[0])
		return (1);
	while ((*e)->env[i])
	{
		if (find_eq_sn((*e)->env[i]) != -1)
			ft_printf("%s\n", (*e)->env[i]);
		i++;
	}
	return (0);
}

//------------------------------------------------------------------------------------------------

int	ft_pwd()
{
	char	cwd[4096];
	if (getcwd(cwd, sizeof(cwd)) != NULL)
		ft_printf("%s\n", cwd);
	else
	{
		perror("pwd");
		return (-1);
	}
	return (0);
}

//------------------------------------------------------------------------------------------------

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

//------------------------------------------------------------------------------------------------

char	*ft_getenv(char *nm_var, t_env *e)
{
	int	i;
	char	*val;

	i = srcd_env(e, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(e->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

int	str_vars(char *str, int fd, t_env *e)
{
	int	i;
	int	ncv;
	char	*nm_var;
	char	*var_val;
	//char	exit_cd;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		/*{
			if (str[i + 1] == '?')
			{
				exit_cd = ft_itoa(last_exit_status);
				if (exit_cd)
				{
					write(fd, exit_cd, ft_strlen(exit_cd));
					free(exit_cd);
				}
				i+=2;
			}
			else*/
			{
				ncv = i + 1;
				while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
					ncv++;
				nm_var = malloc((ncv - (i + 1)) + 1);
				if (!nm_var)
					return (-1);
				ft_strlcpy(nm_var, &str[i + 1], ncv - i);
				nm_var[ncv - (i + 1)] = '\0';
				var_val = ft_getenv(nm_var, e);
				if (var_val)
					write(fd, var_val, strlen(var_val));
				else
					write(fd, "", 0);
				i = ncv;
			}
		//}
		else
		{
			write(fd, &str[i], 1);
			i++;
		}
	}
	return (0);
}

int	ft_echo(char *string, int flag, int fd, t_env *e)
{
	str_vars(string, fd, e);
	if (flag == 0)
		write(1, "\n", 1);
	return (0);
}

//------------------------------------------------------------------------------------------------
/*
int	main(int argc, char *argv[], char **envp)
{
	t_env *e;
	char **h = ft_nsplit("_____________qualcosa=qualcosa__________");
	char **h2 = ft_nsplit("_____________qualcosa");
	char *empty_args[1];
	empty_args[0] = NULL;
	argc+=1;
	argv[0] = argv[0];
	e = malloc(sizeof(t_env));
	init_env(&e, envp);
	ft_export(e, empty_args);
	ft_printf("\n\n");
	ft_export(e, h);
	ft_printf("\n\n");
	ft_export(e, empty_args);
	ft_unset(e, h2);
	ft_export(e, empty_args);
	ft_echo("ciao dio -----------> $_____________qualcosa ", 0, 1, e);
	ft_env(&e);
	return (0);
}*/
