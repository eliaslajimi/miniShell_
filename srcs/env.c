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

int			add_oldpwd()
{
	char	*oldpwd;
	char	*oldpwd_env;

	if ((oldpwd = find_node("PWD")) != NULL)
	{
		oldpwd_env = ft_strdup("OLDPWD=");
		oldpwd = cleannode(oldpwd);
		oldpwd = ft_strjoin(oldpwd_env, oldpwd);
		export_builtin(oldpwd, 0);
	}
	return (0);
}

int	add_pwd()
{
	int		bufsize;
	char	*buf;
	char	*currentdir;
	char	*pwd_env;

	bufsize = 0;
	buf = NULL;
	pwd_env = ft_strdup("PWD=");
	add_oldpwd();
	currentdir = getcwd(buf, bufsize);
	pwd_env = ft_strjoin(pwd_env, currentdir);
	export_builtin(pwd_env, 0);
	free(pwd_env);
	free(buf);
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

int		env_builtin(char **args, int out)
{
	char	*cmd;
	char	*result;
	t_list	*tmp_lst;

	if (args[1] != NULL)
	{
		print("minishell: env: too many arguments\n", 2);
		return(1);
	}
	tmp_lst = g_env;
	cmd = ft_strdup(args[0]);
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
	ft_strdel(&cmd);
	ft_strdel(&result);
	return (0);
}
