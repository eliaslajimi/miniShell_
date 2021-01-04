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
			return (0); //deleting successfull
		}
		if (current->next == NULL)
			break;
		previous = current;
		current = current->next;
	}
	return (127); //node doesn't exist
}

int	unset_builtin(char *arg, char *exportarg)
{
	int		res;
	int		arglen;
	char	*param;
	t_list	*env_lst;

	env_lst = g_env;
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
		res = ft_lstdelnode(&env_lst, param, arglen);
	}
	return (0);
}

int		unset_builtin_loop(char **arg, char *exportarg)
{
	int	ret;

	while (*arg)
	{
		ret = unset_builtin(*arg, exportarg);
		arg++;
	}
	return (ret);
}
