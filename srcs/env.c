#include "minishell.h"

t_list	*setEnv(char **envp)
{
	int		i;
	t_list	*env_lst;
	t_list	*newlst;

	i = 0;
	env_lst = ft_lstnew(NULL);
	env_lst->content = ft_strdup(envp[i++]);
	while (envp[i])
	{
		newlst = ft_lstnew(NULL);
		newlst->content = ft_strdup(envp[i]);
		ft_lstadd_back(&env_lst, newlst);
		i++;
	}
	ft_lstadd_back(&env_lst, NULL);
	return (env_lst);
}

char	*env_builtin(char *flags)
{
	char	*result;
	t_list	*tmp_lst;

	tmp_lst = g_env;
	result = ft_strdup("");
	while (tmp_lst->next)
	{
		result = ft_strjoin(result, tmp_lst->content);
		result = ft_strjoin(result, "\n");
		tmp_lst = tmp_lst->next;
	}
	result = ft_strjoin(result, tmp_lst->content);
	printf("%s\n", result);
	return (result);
}
