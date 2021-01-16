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

int fork_cmd(char *cmd, char **args, int in,  int out)
{
	pid_t	pid;
	char	**env_tab;
	int	*status;

	status = (int*)getglobal(STATUS);
	env_tab = build_env_tab();
	pid = fork();	
	if (pid == 0)//CHILD
	{
		if (in > 0)
		{
			dup2(in, 0);
			close(in);
		}

		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		*status = execve(cmd, args, env_tab);
		exit(*status);
	}
	else if (pid < 0)
	{
		return (-1);
	}
	if (out != 1)
		close(out);

	int childstatus;
	pid_t tpid;
	tpid = wait(&childstatus);
	while (tpid != pid)
	{
		if (tpid != pid)
			kill(tpid, SIGTERM);
		tpid = wait(&childstatus);
	}
	ft_free_array(env_tab);
	return (0);
}
