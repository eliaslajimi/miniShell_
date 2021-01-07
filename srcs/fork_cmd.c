#include "minishell.h"
static char	**build_env_tab()
{
	int		i;
	int		lstsize;
	char	**env_tab;
	t_list	*envlst;

	i = 0;
	envlst = g_env;
	lstsize = ft_lstsize(envlst);
	if (!(env_tab = ft_calloc(lstsize + 1, sizeof(char *))))
		return (NULL);
	env_tab[lstsize] = NULL;
	while (i < lstsize)
	{
		env_tab[i] = ft_strdup(envlst->content);
		envlst = envlst->next;
		i++;
	}
	return (env_tab);
}

int	fork_cmd(char *cmd, char **args)
{
	pid_t	pid;
	char	**env_tab;

	env_tab = build_env_tab();
	pid = fork();
	if (pid < 0)
	{
		print("fork failed", 2);
		return (0);
	}
	else if (pid == 0)
	{
		execve(cmd, args, env_tab);
	}
	else
	{
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM);
	}
	ft_free_array(env_tab);
	return (0);
}
