#include "minishell.h"


char *formatpath(char *path)
{
	if (!ft_strlen(path))
		path = cleannode(find_node("HOME"));
	if (ft_strlen(path) > 1 && path[ft_strlen(path)] == '/')
		path[ft_strlen(path)] = 0;
	if (!ft_strcmp(path, "-"))
		path = cleannode(find_node("OLDPWD"));
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
	arg = formatpath(arg);
	applycmd(arg);
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
