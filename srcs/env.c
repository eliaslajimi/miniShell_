#include "minishell.h"

int add_underscore_main()
{
	t_list	*env_lst;
	t_list	*newnode;

	env_lst = g_env;
	newnode = ft_lstnew("_=/bin/bash");
	ft_lstadd_back(&g_env, newnode);
	return (0);
}

int add_underscore(char *cmd)
{
	t_list	*env_lst;
	t_list	*newnode;
	char	*underscore_env;

	//printf("we add [%s]\n", cmd);
	env_lst = g_env;
	cmd = absolute_path(cmd);
	unset_builtin("_", "void");
	underscore_env = ft_strdup("_=");
	underscore_env = ft_strjoin(underscore_env, cmd);
	newnode = ft_lstnew(underscore_env);
	ft_lstadd_back(&g_env, newnode);
	//free(underscore_env);
	return (0);
}

int add_shlvl()
{
	t_list	*env_lst;
	t_list	*newnode;
	char	*found;

	env_lst = g_env;
	found = find_node("SHLVL");
	if (found == NULL)
	{
		newnode = ft_lstnew("SHLVL=1");
		ft_lstadd_back(&env_lst, newnode);
	}
	else
	{
		export_shlvl(cleannode(find_node("SHLVL")));
	}
	free(found);
	return (0);
}

int	add_oldpwd()
{
	char	*oldpwd;
	char	*oldpwd_env;

	if ((oldpwd = find_node("PWD")) != NULL)
	{
		oldpwd_env = ft_strdup("OLDPWD=");		
		oldpwd = cleannode(oldpwd);		
		oldpwd_env = ft_strjoin(oldpwd_env, oldpwd);		
		//free(oldpwd);		
		export_builtin(oldpwd_env, 0);
		free(oldpwd_env);
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
	free(currentdir);
	free(buf);
	return (0);
}

t_list	*setEnv(char **envp)
{
	int		i;
	t_list	*env_lst;
	t_list	*newlst;

	i = 0;
	env_lst = ft_lstnew(envp[i++]);
	while (envp[i])
	{
		envp[i] = ft_strtrim(envp[i], " ");
		newlst = ft_lstnew(envp[i]);
		ft_lstadd_back(&env_lst, newlst);
		i++;
	}
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
	unset_builtin("_", "void");
	add_underscore("env");
	tmp_lst = g_env;
	cmd = ft_strdup(args[0]);
	result = ft_strdup("");
	while (tmp_lst->next)
	{
		result = ft_strjoin(result, tmp_lst->content);
		result = ft_strjoin(result, "\n");
		tmp_lst = tmp_lst->next;
	}
	result = ft_strjoin(result, tmp_lst->content);
	print(result, out);
	print("\n",out);
	ft_strdel(&cmd);
	ft_strdel(&result);
	return (0);
}
