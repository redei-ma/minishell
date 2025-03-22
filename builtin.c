/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: renato <renato@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 14:17:37 by lacerbi           #+#    #+#             */
/*   Updated: 2025/03/21 20:22:22 by renato           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_env(t_shell **shell, char **envp)
{
	int	n;
	int	i;

	n = 0;
	i = 0;
	while (envp[n])
		n++;
	(*shell)->env = ft_calloc((n + 1), sizeof(char *));
	if (!(*shell)->env)
	{
		free(shell);
		exit(1);
	}
	while(i < n)
	{
		(*shell)->env[i] = ft_strdup(envp[i]);
		if (!(*shell)->env[i])
		{
			ft_freemat((void *)(*shell)->env, i);
			free(shell);
			exit(1);
		}
		i++;
	}
	(*shell)->max = n;
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

int	srcd_env(t_shell *shell, const char *name)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(name);
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], name, len) == 0 && shell->env[i][len] == '=')
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

void	upd_var(t_shell *shell, const char *nm_var, const char *var_val)
{
	int	index;
	int	i;
	char	*n_full_var;
	char	**new_env;

	i = -1;
	index = srcd_env(shell, nm_var);
	n_full_var = var_creation(nm_var, var_val);
	if (!n_full_var)
		return ;
	if (index != -1)
	{
		free(shell->env[index]);
		shell->env[index] = n_full_var;
	}
	else
	{
		new_env = malloc(sizeof(char *) * (shell->max + 2));
		if (!new_env)
		{
			free(n_full_var);
			return;
		}
		while (++i < shell->max)
			new_env[i] = shell->env[i];
		new_env[i] = n_full_var;
		new_env[i + 1] = NULL;
		free(shell->env);
		shell->env = new_env;
		shell->max++;
	}
}

int	ft_export(t_shell *shell, char **args)
{
	int			i;
	int			eqp;
	char		*name;
	char		*val;

	if (!args[0])
	{
		i = 0;
		while (shell->env[i])
		{
			ft_printf("declare -x %s\n", shell->env[i]);
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
			upd_var(shell, name, val);
			free(name);
			free(val);
		}
		else if (srcd_env(shell, args[i]) == -1)
			upd_var(shell, args[i], "");
		i++;
	}
	return (0);
}

//------------------------------------------------------------------------------------------------

void	ft_unset(t_shell *shell, char **args)
{
	int	index;
	int	i;
	int	j;

	if (!args[0])
		return ;
	i = 0;
	while (args[i])
	{
		index = srcd_env(shell, args[i]);
		if (index != -1)
		{
			free(shell->env[index]);
			j = index;
			while (shell->env[j])
			{
				shell->env[j] = shell->env[j + 1];
				j++;
			}
			shell->max--;
		}
		i++;
	}
}

//------------------------------------------------------------------------------------------------

int	ft_env(t_shell **shell)
{
	int	i;

	i = 0;
	if (!shell || !shell[0])
		return (1);
	while ((*shell)->env[i])
	{
		if (find_eq_sn((*shell)->env[i]) != -1)
			ft_printf("%s\n", (*shell)->env[i]);
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

char	*ft_getenv(char *nm_var, t_shell *shell)
{
	int	i;
	char	*val;

	i = srcd_env(shell, nm_var);
	if (i == -1)
		return (NULL);
	val = ft_strchr(shell->env[i], '=');
	if (val)
		return (val + 1);
	return (NULL);
}

int	handle_quotes(char c, int *in_single_quote, int *in_double_quote)
{
	if (c == '\'' && !(*in_double_quote))
	{
		*in_single_quote = !(*in_single_quote);
		return (1);
	}
	else if (c == '"' && !(*in_single_quote))
	{
		*in_double_quote = !(*in_double_quote);
		return (1);
	}
	return (0);
}

int	handle_exit_status(t_shell *shell)
{
	char *exit_cd = ft_itoa(last_exit_status);
	if (!exit_cd)
		return (-1);
	write(shell->cmds->file_i, exit_cd, ft_strlen(exit_cd));
	free(exit_cd);
	return (0);
}

int	handle_env_variable(char *str, int i, t_shell *shell)
{
	int ncv = i + 1;
	char *nm_var;
	char *var_val;

	while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
		ncv++;
	nm_var = malloc((ncv - (i + 1)) + 1);
	if (!nm_var)
		return (-1);
	ft_strlcpy(nm_var, &str[i + 1], ncv - i);
	nm_var[ncv - (i + 1)] = '\0';
	var_val = ft_getenv(nm_var, shell);
	if (var_val)
		write(shell->cmds->file_i, var_val, strlen(var_val));
	else
		write(shell->cmds->file_i, "", 0);
	free(nm_var);
	return (ncv);
}

int	handle_variable(char *str, int i, t_shell *shell)
{
	if (str[i + 1] == '?')
	{
		if (handle_exit_status(shell) == -1)
			return (-1);
		return (i + 2);
	}
	else
	{
		return handle_env_variable(str, i, shell);
	}
}

int	str_vars(char *str, t_shell *shell)
{
	int	i;
	int	in_single_quote;
	int	in_double_quote;

	i = 0;
	in_single_quote = 0;
	in_double_quote = 0;
	while (str[i] != '\0')
	{
		if (handle_quotes(str[i], &in_single_quote, &in_double_quote))
			i++;
		else if (str[i] == '$' && !in_single_quote)
		{
			i = handle_variable(str, i, shell);
			if (i == -1)
				return (-1);
		}
		else
		{
			write(shell->cmds->file_i, &str[i], 1);
			i++;
		}
	}
	return (0);
}
/*
int	str_vars(char *str, t_shell *shell)
{
	int	i;
	int	ncv;
	char	*nm_var;
	char	*var_val;
	int	in_single_quote = 0;
	int	in_double_quote = 0;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'' && !in_double_quote)
		{
			in_single_quote = !in_single_quote;
			i++;
		}
		else if (str[i] == '"' && !in_single_quote)
		{
			in_double_quote = !in_double_quote;
			i++;
		}
		else if (str[i] == '$' && !in_single_quote)
		{
			if (str[i + 1] == '?')
			{
				exit_cd = ft_itoa(last_exit_status);
				if (exit_cd)
				{
					write(shell.cmds->file_i, exit_cd, ft_strlen(exit_cd));
					free(exit_cd);
				}
				i+=2;
			}
			else
			{
				ncv = i + 1;
				while (str[ncv] != '\0' && (ft_isalnum(str[ncv]) || str[ncv] == '_'))
					ncv++;
				nm_var = malloc((ncv - (i + 1)) + 1);
				if (!nm_var)
					return (-1);
				ft_strlcpy(nm_var, &str[i + 1], ncv - i);
				nm_var[ncv - (i + 1)] = '\0';
				var_val = ft_getenv(nm_var, shell);
				if (var_val)
					write(shell->cmds->file_i, var_val, strlen(var_val));
				else
					write(shell->cmds->file_i, "", 0);
				i = ncv;
			}
		}
		else
		{
			write(shell->cmds->file_i, &str[i], 1);
			i++;
		}
	}
	return (0);
}*/

int	cmp_echo_flag(char *str)
{
	if (ft_strncmp(str[0], "-n", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "\"-n\"", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "\"-\"n", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "-\"n\"", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "\'-n\'", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "\'-\'n", ft_strlen(args[0])) == 0)
		return (1);
	else if (ft_strncmp(str[0], "-\'n\'", ft_strlen(args[0])) == 0)
		return (1);
	return (0);
}

int	ft_echo(t_shell *shell)
{
	int i;

	i = 0;
	if (shell->cmds->args && cmp_echo_flag(shell->cmds->args[i]))
	{
		while (shell->cmds->args[i + 1])
		{
			str_vars(shell->cmds->args[i + 1], shell);
			i++;
		}
	}
	else
	{
		while (shell->cmds->args[i])
		{
			str_vars(shell->cmds->args[i], shell);
			i++;
		}
	}
	return (0);
}

//------------------------------------------------------------------------------------------------

void	handle_ctrl_c(int signum)
{
	(void)signum;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	handle_ctrl_bl(int signum)
{
	(void)signum;
}

void	interactive_ctrls(void)
{
	struct sigaction sa_int;
	struct sigaction sa_quit;

	sa_int.sa_handler = handle_ctrl_c;
	sigemptyset(&sa_int.sa_mask);
	sa_int.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa_int, NULL);

	sa_quit.sa_handler = handle_ctrl_bl;
	sigemptyset(&sa_quit.sa_mask);
	sa_quit.sa_flags = SA_RESTART;
	sigaction(SIGQUIT, &sa_quit, NULL);
}

void	ni_ctrls(void)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, handle_ctrl_bl);
}

//------------------------------------------------------------------------------------------------

void	ft_exit(t_shell *shell, char **args)
{
	int	exit_code = 0;

	write(1, "exit\n", 5);
	if (args[1])
	{
		if (ft_atoi(args[1]) == 0 && (args[1][0] != 0 || args[1][0] != '\0'))
		{
			write(2, "exit: numeric argument required\n", 44);
			//exit_code = 255;
		}
		else if (args[2])
		{
			write(2, "exit: too many arguments\n", 36);
			return ;
		}
		else
			exit_code = ft_atoi(args[1]) % 256;
	}
	//free_shell(shell);
	exit(exit_code);
}

//------------------------------------------------------------------------------------------------

int	main(int argc, char *argv[], char **envp)
{
	t_shell *e;
	char **h = ft_nsplit("cosa=PORCONE");
	//char **h2 = ft_nsplit("_____________qualcosa");
	char *empty_args[1];
	empty_args[0] = NULL;
	argc+=1;
	argv[0] = argv[0];
	e = malloc(sizeof(t_shell));
	e->cmds = malloc(sizeof(t_cmd));
	e->cmds->file_i = 1;
	init_env(&e, envp);
	ft_export(e, empty_args);
	ft_printf("\n\n");
	ft_export(e, h);
	ft_printf("\n\n");
	ft_env(&e);
	//ft_export(e, empty_args);
	//ft_unset(e, h2);
	//ft_export(e, empty_args);
	char **g = malloc(3 * sizeof(char *));
	g[0] = "-n";
	g[1] = "'\"$cosa'$cosa'\"'";
	g[2] = NULL;
	
	ft_echo(g, e);
	//ft_env(&e);
	return (0);
}
