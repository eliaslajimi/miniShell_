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

int	fork_cmd(char *cmd)
{
	pid_t	pid;
	char	*new_argv[2]; //!!! new_argv doit être le ctable->args sous forme de char **
	char	**env_tab;

	new_argv[0] = ft_strdup(cmd);
	new_argv[1] = NULL;
	env_tab = build_env_tab();
	pid = fork();
	if (pid < 0)
	{
		print("fork failed", 2);
		ft_strdel(&new_argv[0]);
		return (0);
	}
	else if (pid == 0)
	{
		execve(cmd, new_argv, env_tab);
	}
	else
	{
		waitpid(pid, 0, 0);
		kill(pid, SIGTERM);
	}
	ft_strdel(&new_argv[0]);
	ft_free_array(env_tab);
	return (0);
}
