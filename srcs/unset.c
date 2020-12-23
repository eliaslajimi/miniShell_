#include "minishell.h"

int	unsetfunc(char *arg, char *exportarg)
{
	int		res;
	int		arglen;
	char	*param;
	t_list	*env_lst;

	env_lst = g_env;
	if (ft_strcmp(arg, "") != 0)
	{
		if (ft_strcmp(exportarg, "void") != 0)
			param = arg;
		else
			param = exportarg;
		arglen = ft_strlen(param);
		res = ft_lstdelnode(&env_lst, param, arglen);
	}
	return (0);
}
