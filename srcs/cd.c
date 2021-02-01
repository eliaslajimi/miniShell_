#include "minishell.h"


char *formatpath(char *path)
{
	char	*tmp;
	if (!ft_strlen(path))
		if (!(path = cleannode(find_node("HOME"))))
		{
			print("minishell: cd: HOME not set\n", 1);
			return (NULL);
		}
	if (ft_strlen(path) > 1 && path[ft_strlen(path)] == '/')
		path[ft_strlen(path)] = 0;
	if (!ft_strcmp(path, "-"))
		path = cleannode(find_node("OLDPWD"));
	if ((!ft_strcmp(path, "~")) || (!ft_strncmp(path, "~/", 2)))
	{
		path++;
		tmp = path;
		path = ft_strjoin(ft_strjoin(ft_strdup(cleannode(find_node("HOME"))), "/"), path + 1);
		free(tmp); 
	}
	if (!ft_strncmp(path, "./", 2))
	{
		tmp = path;
		path = ft_strtrim(path, "./");
		free(tmp);
	}
	return (path);
}

int applycmd(char *cmd)
{
	int		status;
	char	*tmp;
	char	*newcmd;

	newcmd = NULL;
	status = 0;
	if (!ft_strcmp(cmd, ""))
		status = chdir(cleannode(find_node("HOME")));
	if (cmd[0] == '~' || cmd[0] == '/')
		status = chdir(cmd);
	else
	{
		tmp = cmd;
		cmd = ft_strtrim(cmd, "/");
		free(tmp);
		cmd = ft_strjoin(cmd, "/");
		if (!ft_strcmp(cleannode(find_node("PWD")), "/"))
			newcmd = ft_strjoin(ft_strdup(cleannode(find_node("PWD"))), cmd);
		else
			newcmd = ft_strjoin(ft_strjoin(ft_strdup(cleannode(find_node("PWD"))), "/"), cmd);
		status = chdir(newcmd);
		free(newcmd);
	}
	if (!status)
		add_pwd();
	free(cmd);
	return (status);
}

char *getaccesserr(char *path)
{
	opendir(path);
	if (errno == EACCES)
		return (": Permission denied");
	return (": No such file or directory");
	
}
int argtocmd(char *arg)
{
	int *status;
	char *arg2;

	if (!arg)
		return (0);
	status = (int*)getglobal(STATUS);
	if (!(arg2 = formatpath(ft_strdup(arg))))
		return (0);
	*status = applycmd(arg2);
	if (*status != 0)
	{
		print("minishell: ", 1);
		print("cd: ", 1);
		print(arg, 1);
		print(getaccesserr(arg), 1);
		//print(": No such file or directory", 1);
		print("\n", 1);
	}
	return (0);
}

char **removeidentical(char **cmd)
{
	while (cmd && *cmd && *(cmd+1))
	{
		if (ft_strcmp(*cmd, *(cmd + 1)))
			return (cmd);
		cmd++;
	}
	return (cmd);
}

int cd(char **args, int in, int out)
{
	int status;

	status = 0;
	(void)in;
	(void)out;
	args++;
	if (!ptr_len((void*)args))
		argtocmd("");
	if (*args)
	{
		if (!ft_strlen(*args))
			*args = ft_strjoin(*args, cleannode(find_node("PWD")));
		args = removeidentical(args);	
	    argtocmd(*args);
		args++;
	}

	return (status);
}
