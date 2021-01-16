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

void	next_exec(c_table **ctable)
{
	if (!(*ctable)->id)
		exit(*(int*)getglobal(STATUS));
}

int	other_command(c_table *ctable)
{
		int status;
		ctable->command = ft_strdup(absolute_path(ctable->command));
	
		add_underscore(ctable->command);
		if (ctable->command[0] != '/')
		{
			print("minishell: ", 2);
			print(ctable->command, 2);
			print(": command not found\n", 2);
			status = 127;
		}
		else
		{
			status = fork_cmd(ctable->command, ctable->args, ctable->in, ctable->out);
		}
	return (status);
}

void	commands(c_table *ctable)
{
	int	*status;

	status = (int*)getglobal(STATUS);
	if (ft_strcmp(ctable->command, "exit") == 0)
		exit_builtin(ctable->args);
	else if (ft_strcmp(ctable->command, "echo") == 0)
		*status = echo(ctable->args, ctable->in, ctable->out);
	else if (ft_strcmp(ctable->command, "env") == 0)
		*status = env_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "unset") == 0)
		*status = unset_builtin_loop(ctable->args, "void");
	else if (ft_strcmp(ctable->command, "export") == 0)
		*status = export_builtin_loop(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "pwd") == 0)
		*status = pwd_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "cd") == 0)
		*status = cd(ctable->args, ctable->in, ctable->out);
	else
		*status = other_command(ctable);
	next_exec(&ctable);
}

int	pipehandler(c_table *ctable)
{
	if (ctable->pipeout)
		ctable->next->in = setpipe(&ctable->out);
	return (0);
}


int	piperoutine(c_table *ctable)
{
	pipehandler(ctable);
	if (!(ctable->id = fork()))//CHILD
		return (0);
	else if (ctable->id)//PARENT
	{
		ctable->next->id = ctable->id;
		ctable = ctable->next;
		executor(ctable);
	}
	fflush(stdout);
	return (0);
}

void	executor(c_table *ctable)
{
	if (ctable == NULL)
		return ;
	if (ft_strcmp(ctable->fileout, "") != 0)
		ctable->out = getfd(ctable->fileout, ctable->out);
	if (ctable->pipeout)	
		piperoutine(ctable);
	commands(ctable);
	ctable = ctable->next;
	executor(ctable);
}

