#include "minishell.h"

int		export_builtin(char *arg)
{
	int		i;
	char	**split_arg;
	t_list	*env_lst;
	t_list	*newnode;

	i = 0;
	env_lst = g_env;
	if (ft_isin('=', arg))
	{
		split_arg = ft_split(arg, '=');
		if (find_node(&env_lst, split_arg[0]) != NULL)
			unsetfunc(env_lst, split_arg[0], "void");
		ft_free_array(split_arg);
		while (arg[i] != '=')
			i++;
		if (i == 0)
			return (1);
		newnode = ft_lstnew(NULL);
		newnode->content = ft_strdup(arg);
		ft_lstadd_back(&env_lst, newnode);
	}
	else
	{
		return (print_sorted_list(env_lst));
	}

	return (0);
}
