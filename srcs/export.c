#include "minishell.h"

static void		shlvl_err_msg(int shlvl)
{
	write(1, "minishell: warning: shell level (",
		ft_strlen("minishell: warning: shell level ("));
	ft_putnbr_fd(shlvl, STDERR_FILENO);
	ft_putstr_fd(") too high, resetting to 1\n", STDERR_FILENO);
}

int					export_shlvl(char *nb)
{
	char	*itoa_shlvl;
	t_list	*env_lst;
	t_list	*newnode;
	int		shlvl;
	char	*toexport;
	
	env_lst = g_env;
	shlvl = (int)ft_atoi_shlvl(nb);
	shlvl++;
	(shlvl < 0) ? shlvl = 0 : shlvl;
	if (shlvl > 1000)
	{
		if (shlvl < INT_MAX)
			shlvl_err_msg(shlvl);
		shlvl = 1;
	}
	toexport = ft_strdup("SHLVL=");
	itoa_shlvl = ft_itoa(shlvl);
	toexport = ft_strjoin(toexport, itoa_shlvl);
	free(itoa_shlvl);
	if (find_node("SHLVL") != NULL)
		unset_builtin("SHLVL", "void");
	newnode = ft_lstnew(toexport);
	ft_lstadd_back(&env_lst, newnode);
	free(toexport);
	return (0);
}

int			export_builtin(char *arg, int out)
{
	int		i;
	char	**split_arg;
	t_list	*env_lst;
	t_list	*newnode;
	char	*found;

	i = 0;
	env_lst = g_env;

	int k ;
	if (arg[0] == '\0')
	{
		print("minishell: export: `': not a valid identifier\n", 2);
		return (1);
	}
	else if (ft_isin(arg[0], "0123456789="))
	{
		print("minishell: export: `", 2);
		print(arg, 2);
		print("': not a valid identifier\n", 2);
		return (1);
	}
	else if (ft_isin('=', arg))
	{
		int j = 0;

		split_arg = ft_split(arg, '=');
		if (ft_strcmp(split_arg[0], "SHLVL") == 0)
		{
			if (split_arg[1])
				export_shlvl(split_arg[1]);
			else
				export_shlvl("1");
			ft_free_array(split_arg);
			return (0);
		}
		while (split_arg[0][j])
		{
			if (ft_isin(split_arg[0][j], "\'\"\\$@!|;& "))
			{
				print("minishell: export: `", 2);
				print(arg, 2);
				print("': not a valid identifier\n", 2);
				return(1);
			}
			j++;
		}
		found = find_node(split_arg[0]);
		if (found != NULL)
		{
			unset_builtin(split_arg[0], "void");
		}
		free(found);
		ft_free_array(split_arg);
		while (arg[i] != '=')
			i++;
		if (i == 0)
			return (1);
		newnode = ft_lstnew(arg);
		ft_lstadd_back(&env_lst, newnode);
		return (0);
	}
	else if (ft_strcmp(arg, "null") == 0)
	{
		return (join_sorted_list(env_lst, out));
	}
	else
	{
		k = 0;
		while (arg[k])
		{
			if (ft_isin(arg[k], "\'\"\\$@!|;& "))
			{
				print("minishell: export: `", 2);
				print(arg, 2);
				print("': not a valid identifier\n", 2);
				return (1);
			}
			k++;
		}
	}
	return (0);
}

int			export_builtin_loop(char **arg, int args_len, int out)
{
	int		i;
	int		ret;
	char	*underscore;

	ret = 0;
	i = 1;
	arg++;
	while (i < args_len)
	{
		ret = export_builtin(*arg, out);
		arg++;
		i++;
	}
	arg--;
	i=0;
	while((*arg)[i] && (*arg)[i] != '=')
		i++;
	underscore = ft_strndup(*arg, i);
	add_underscore(underscore);
	if (args_len == 1)
		export_builtin("null", out);
	return (ret);
}
