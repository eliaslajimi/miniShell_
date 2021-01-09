#include "minishell.h"


char *formatpath(char *path)
{
	if (!ft_strlen(path))
		path = cleannode(find_node("HOME"));
	if (ft_strlen(path) > 1 && path[ft_strlen(path)] == '/')
		path[ft_strlen(path)] = 0;
	if (!ft_strcmp(path, "-"))
		path = cleannode(find_node("OLDPWD"));
	if ((!ft_strcmp(path, "~")) || (!ft_strncmp(path, "~/", 2)))
	{
		path++;
		path = ft_strjoin(ft_strjoin(ft_strdup(cleannode(find_node("HOME"))), "/"), path + 1);
	 }
	return (path);
}

int applycmd(char *cmd)
{
	int status;

	status = 0;
	if (!ft_strcmp(cmd, ""))
		status = chdir(cleannode(find_node("HOME")));
	if (cmd[0] == '~' || cmd[0] == '/')
		status = chdir(cmd);
	else
		status = chdir(ft_strjoin(ft_strjoin(ft_strdup(cleannode(find_node("PWD"))), "/"), cmd));
	if (!status)
		add_pwd();
	return (status);
}

int argtocmd(char *arg)
{
	int *status;

	status = (int*)getglobal(STATUS);
	arg = formatpath(arg);
	*status = applycmd(arg);
	if (*status != 0)
	{
		print("cd: no such file or directory: ", 1);
		print(arg, 1);
		print("\n", 1);
	 }

	return (0);
}

int cd(char **args, int in, int out)
{
	int status;

	status = 0;
	(void)in;
	(void)out;
	args++;
	if (*args == NULL)
		argtocmd("");
	while (*args)
	{
	    argtocmd(*args);
		args++;
	}
	return (status);
}
