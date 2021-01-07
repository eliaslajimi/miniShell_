#include "minishell.h"

int add_underscore(char *cmd)
{
	t_list	*env_lst;
	t_list	*newnode;
	char	*underscore_env;

	env_lst = g_env;
	unset_builtin("_", "void");
	underscore_env = ft_strdup("_=");
	underscore_env = ft_strjoin(underscore_env, cmd);
	newnode = ft_lstnew(NULL);
	newnode->content = ft_strdup(underscore_env);
	ft_lstadd_back(&g_env, newnode);
	ft_strdel(&underscore_env);
	return (0);
}

int add_shlvl()
{
	char	*shlvl;

	shlvl = ft_strdup("SHLVL=");
	shlvl = ft_strjoin(shlvl, "1");
	export_builtin(shlvl, 0);
	ft_strdel(&shlvl);
	return (0);
}

int	add_pwd()
{
	int		bufsize;
	char	*buf;
	char	*currentdir;
	char	*pwd_env;

	pwd_env = ft_strdup("PWD=");
	bufsize = 0;
	buf = NULL;
	currentdir = getcwd(buf, bufsize);
	free(buf);
	pwd_env = ft_strjoin(pwd_env, currentdir);
	export_builtin(pwd_env, 0);
	free(pwd_env);
	return (0);
}

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

int		env_builtin(char *cmd, int out)
{
	char	*result;
	t_list	*tmp_lst;

	tmp_lst = g_env;
	result = ft_strdup("");
	add_underscore(cmd);
	while (tmp_lst->next)
	{
		result = ft_strjoin(result, tmp_lst->content);
		result = ft_strjoin(result, "\n");
		tmp_lst = tmp_lst->next;
	}
	result = ft_strjoin(result, tmp_lst->content);
	print(result, out);
	return (0);
}
