#include "minishell.h"

int	getfd(char *file, int mode)
{
	int	fd;
	fd = open(file, mode);
	return (fd);
}

int	setpipe(int *fdin)
{
	int fd[2];
	pipe(fd);
	if (*fdin == 1)		/*only applies pipe if no file redirection*/
		*fdin = fd[1];
	return (fd[0]);
}

void	next_exec(c_table *ctable)
{
	c_table	*n;

	n = ctable;
	if (ctable->pipein && !ctable->pipeout)
	{
		while (ctable)
			if ((n = ctable) && (ctable = ctable->next))	
				free_struct(n);
		exit(0);
	}
	if ((ctable = ctable->next) && (ctable))
		executor(ctable);
}

int	commands(c_table *ctable)
{
	int ret;

	ret = 0;
//	printf("command is %s\n", ctable->command);
//	printf("first arg is %s\n", ctable->args);
	if (ft_strcmp(ctable->command, "echo") == 0)
		ret = echo(ctable->args, ctable->flags, ctable->in, ctable->out);
	else if (ft_strcmp(ctable->command, "env") == 0)
		ret = env_builtin(ctable->out);
	else if (ft_strcmp(ctable->command, "unset") == 0)
		ret = unset_builtin(ctable->args, "void");
	else if (ft_strcmp(ctable->command, "export") == 0)
		ret = export_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "pwd") == 0)
		ret = pwd_builtin(ctable->out);
	else
	{
		ctable->command = ft_strdup(absolute_path(ctable->command));
		if (ctable->command[0] != '/')
		{
			print("minishell: ", 2);
			print(ctable->command, 2);
			print(": command not found\n", 2);
			ret = 127;
		}
		else
			fork_cmd(ctable->command);
	}
	//print_struct(ctable);
	next_exec(ctable);
	return (ret);
}

void	executor(c_table *ctable)
{
	if (ctable->pipeout)
		ctable->next->pipein = setpipe(&ctable->out);
	if (ctable->pipein)
		ctable->in = ctable->pipein;
	if (ft_strcmp(ctable->filein, "") != 0)
		ctable->in = getfd(ctable->filein, ctable->in);
	if (ft_strcmp(ctable->fileout, "") != 0)
		ctable->out = getfd(ctable->fileout, ctable->out);
	if (ctable->pipeout && !(id = fork()))
		executor(ctable->next);
	commands(ctable);
}

