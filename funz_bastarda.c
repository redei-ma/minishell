void	exit_status_var(char **expanded, int *iter_arr, t_shell *shell)
{
	char *status;

	status = ft_itoa(g_exit_status);
	if (!status)
	{
		free(expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	expanded = ft_realloc(expanded, (iter_arr[2] + 1) * sizeof(char), (iter_arr[2] + ft_strlen(status) - 2 + 1) * sizeof(char));
	if (!expanded)
	{
		free(status);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(expanded + iter_arr[1], status, ft_strlen(status) + 1);
	iter_arr[1] += ft_strlen(status);
	iter_arr[0] += 2;
	iter_arr[2] += ft_strlen(status) - 2;
	free(status);
}

void	var_cases(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	int		x;
	char	*var

	x = iter_arr[0];
	var = handle_env_variable(str, &iter_arr[0], shell);
	if (!var)
	{
		free(expanded);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	expanded = ft_realloc(expanded, (iter_arr[2] + 1) * sizeof(char), (iter_arr[2] + ft_strlen(var) - (iter_arr[0] - x)  + 1) * sizeof(char)); //manca quanto misura la var dopo dollaro
	if (!expanded)
	{
		free(var);
		exit_all("Error: malloc failed\n", shell, 1);
	}
	ft_strlcpy(expanded+iter_arr[1], var, ft_strlen(var)+1);
	iter_arr[1] += ft_strlen(var);
	free(var);
}

void	stoplight(char **expanded, int *iter_arr, t_shell *shell, char *str)
{
	if (str[iter_arr[0] + 1] == '?')
		exit_status_var(expanded, iter_arr, shell);
	else if (ft_isalnum(str[iter_arr[0]+1]) || str[iter_arr[0]+1] == '_')
		var_cases(expanded, iter_arr, shell, str);
	else
		expanded[iter_arr[1]++] = str[iter_arr[0]++];
}

//iter_arr : array che contiene i vari iteratori quali i, j, ecc....
//in_sd_qts : array che contiene le variabili che rappresentavano in_single_quotes e in_double_quotes...

char *expander(char *str, t_shell *shell)
{
	int		iter_arr[3];
	int		in_sd_qts[2];
	char 	*expanded;

	iter_arr[2] = ft_strlen(str);
	iter_arr[0] = 0;
	iter_arr[1] = 0;
	in_sd_qts[0] = 0;
	in_sd_qts[1] = 0;
	expanded = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	if (!expanded)
		return (NULL);
	while (str[iter_arr[0]])
	{
		if (handle_quotes(str[iter_arr[0]], &in_sd_qts[0], &in_sd_qts[1]))
		{
			iter_arr[0]++;
			continue;
		}
		if (str[iter_arr[0]] == '$' && !in_sd_qts[0])
			stoplight(expanded, iter_arr, shell, str);
		else
			expanded[iter_arr[1]++] = str[iter_arr[0]++];
	}
	free(str);
	return (expanded);
}
