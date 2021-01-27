#include "minishell.h"

static int	 ft_lstdelnode(t_list **lst, char *data, int datalen)
{
	t_list	*current;
	t_list	*previous;

	previous = NULL;
	current = *lst;
	while (current)
	{
		if (ft_strncmp(current->content, data, datalen) == 0 &&
				(ft_strncmp((char*)(current->content) + datalen, "=", 1)) == 0)
		{
			if (previous == NULL)
				*lst = current->next;
			else
				previous->next = current->next;
			free(current);
			return (0);
		}
		if (current->next == NULL)
			break;
		previous = current;
		current = current->next;
	}
	return (127);
}

int	unset_builtin(char *arg, char *exportarg)
{
	int		k;
	int		ret;
	int		arglen;
	char	*param;
	t_list	*env_lst;

	ret = 0;
	env_lst = g_env;
	if (arg[0] == '\0')
	{
		print("minishell: unset: `': not a valid identifier\n", 2);
		return (1);
	}
	k = 0;
	while (arg[k])
	{
		if (ft_isin(arg[k], "\'\"\\$@!|;&= "))
		{
			print("minishell: unset: `", 2);
			print(arg, 2);
			print("': not a valid identifier\n", 2);
			return (1);
		}
		k++;
	}
	if (ft_strcmp(arg, "") != 0)
	{
		if (ft_strcmp(exportarg, "void") == 0)
		{
			param = arg;
		}
		else
		{
			param = exportarg;
		}
		arglen = ft_strlen(param);
		//printf("\nwe unset [%s]\n", param);
		ret = ft_lstdelnode(&env_lst, param, arglen);
	}
	return (ret);
}

int		unset_builtin_loop(char **arg, char *exportarg)
{
	int	final_ret;
	int	ret;

	arg++;
	final_ret = 0;
	while (*arg)
	{
		ret = unset_builtin(*arg, exportarg);
		if (ret != 0)
			final_ret = ret;
		arg++;
	}
	arg--;
	add_underscore(*arg, 0);
	return (final_ret);
}