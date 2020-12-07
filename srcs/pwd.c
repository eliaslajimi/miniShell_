#include "minishell.h"

void	pwd_builtin(t_list *env_list)
{
	while (env_list->next)
	{
		if (ft_strncmp(env_list->content, "PWD", 3))
			printf("%s\n", env_list->content + 4);
		env_list = env_list->next;
	}
	if (ft_strncmp(env_list->content, "PWD", 3))
		printf("%s\n", env_list->content + 4);
}
