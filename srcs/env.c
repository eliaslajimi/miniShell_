#include "minishell.h"

t_list	*get_env_var(char **envp)
{
	int	i;
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

int		env_builtin(t_list *env_lst, int fd)
{
	char	*result;
	t_list	*tmp;

	tmp = env_lst;
	result = NULL;
	while (tmp->next)
	{
		printf("%s\n", tmp->content);
		//ft_putendl_fd(tmp->content, fd);
		//result = ft_strjoin(result, tmp->content);
		tmp = tmp->next;
	}
	result = ft_strjoin(result, tmp->content);
	return (0);
}
