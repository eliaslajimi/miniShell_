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
	if (ctable->pipein && !ctable->pipeout)
	{
		exitroutine();
		exit(*((int*)getglobal(STATUS)));
	}
	if ((ctable = ctable->next) && (ctable))
		executor(ctable);
}

//*status = echo(ctable->args[0], ctable->flags, ctable->in, ctable->out); <-- PROTOTYPE FOR BUILTIN || 
//should refactor builtin with proper prototype
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
			status = fork_cmd(ctable->command);
		}
	return (status);
}

void	commands(c_table *ctable)
{
	int	*status;

	status = (int*)getglobal(STATUS);
	if (ft_strcmp(ctable->command, "exit") == 0)
		exit(*((int*)getglobal(STATUS)));
	else if (ft_strcmp(ctable->command, "echo") == 0)
		*status = echo(ctable->args[0], ctable->flags, ctable->in, ctable->out);
	else if (ft_strcmp(ctable->command, "env") == 0)
		*status = env_builtin(ctable->command, ctable->out);
	else if (ft_strcmp(ctable->command, "unset") == 0)
		*status = unset_builtin_loop(ctable->args, "void");
	else if (ft_strcmp(ctable->command, "export") == 0)
		*status = export_builtin_loop(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "pwd") == 0)
		*status = pwd_builtin(ctable->out);
	else
		*status = other_command(ctable);
	next_exec(ctable);
}

void	executor(c_table *ctable)
{
	//print_struct(ctable);
	print_struct(ctable);
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

