#include "minishell.h"

int			export_builtin(char *arg, int out)
{
	int		i;
	char	**split_arg;
	t_list	*env_lst;
	t_list	*newnode;

	i = 0;
	env_lst = g_env;

	int k = 0;
	while (arg[k])
	{
		if (ft_isin(arg[k], "\'\"\\$@!|;& "))
		{
			print("minishell: export: `", 2);
			print(arg, 2);
			print("': not a valid identifier\n", 2);
			exit(1);
		}
		k++;
	}
	if (ft_isin(arg[0], "0123456789="))
	{
		print("minishell: export: `", 2);
		print(arg, 2);
		print("': not a valid identifier\n", 2);
		exit(1);
	}
	else if (ft_isin('=', arg))
	{
		split_arg = ft_split(arg, '=');
		
		int j = 0;
		while (split_arg[0][j])
		{
			if (ft_isin(split_arg[0][j], "\'\"\\$@!|;&"))
			{
				print("minishell: export: `", 2);
				print(arg, 2);
				print("': not a valid identifier\n", 2);
				exit(1);
			}
			j++;
		}
		if (find_node(split_arg[0]) != NULL)
		{
			unset_builtin(split_arg[0], "void");
		}
		ft_free_array(split_arg);
		while (arg[i] != '=')
			i++;
		if (i == 0)
			return (1);
		newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(arg);
		ft_lstadd_back(&env_lst, newnode);
		return (0);
	}
	else if (ft_strcmp(arg, "null") == 0)
	{
//		add_underscore("export");
		return (join_sorted_list(env_lst, out));
	}
	return (0);
}

int			export_builtin_loop(char **arg, int out)
{
	int		ret;

	ret = 0;

	arg++;
	if (arg && *arg)
	{
		while (*arg)
		{
			ret = export_builtin(*arg, out);
			arg++;
		}
	}
	else
		export_builtin("null", out);
	return (ret);
}
