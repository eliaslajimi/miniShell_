#include "minishell.h"

int	getfd(char *file, int mode)
{
	int	fd;
	fd = open(file, mode, 777);
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
	{
		exit(*(int*)getglobal(STATUS));
	}
}

int	other_command(c_table *ctable)
{
		int status;
		ctable->command = ft_strdup(absolute_path(ctable->command));
	
		add_underscore(ctable->command);
		//int ret = 0;
		status= 0;
		if (ctable->command[0] != '/' && ctable->command[0] != '.')
		{
			if (open(ctable->command, O_RDONLY))
			{
				print("minishell: ", 2);
				print(ctable->command, 2);
				print(": command not found\n", 2);
				status = 127;
			}
		}
		else
		{
		status = fork_cmd(ctable->command, ctable->args, ctable);
		}
	return (status);
}

void	commands(c_table *ctable)
{
	int	*status;

	status = (int*)getglobal(STATUS);
	if (!ft_strlen(ctable->command))
	{
		*status = 0;
		return ;
	}
	if (ft_strcmp(ctable->command, "exit") == 0)
		exit_builtin(ctable->args);
	else if (ft_strcmp(ctable->command, "echo") == 0)
		*status = echo(ctable->args, ctable->args_len, ctable->in, ctable->out);
	else if (ft_strcmp(ctable->command, "env") == 0)
		*status = env_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "unset") == 0)
		*status = unset_builtin_loop(ctable->args, "void");
	else if (ft_strcmp(ctable->command, "export") == 0)
		*status = export_builtin_loop(ctable->args, ctable->args_len, ctable->out);
	else if (ft_strcmp(ctable->command, "pwd") == 0)
		*status = pwd_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "cd") == 0)
		*status = cd(ctable->args, ctable->in, ctable->out);
	else
		*status = other_command(ctable);
	if (ctable->id > 0)
		kill(ctable->id, 0);
	next_exec(&ctable);
}

int	pipehandler(c_table *ctable)
{
	if (ctable->pipeout)
		ctable->next->in = setpipe(&ctable->out);
	return (0);
}


int	piperoutine(c_table **ctable)
{
	int fd[2];
	int pid;

	pipe(fd);
	pid = fork();
	if (!pid)//CHILD
	{
		close(fd[0]);
		(*ctable)->id = pid;
		(*ctable)->out = fd[1];	
		return (0);
	}
	close(fd[1]);
	(*ctable)->id = pid;
	(*ctable)->next->id = (*ctable)->id;
	next_struct(ctable);
	(*ctable)->in = fd[0];
	return (1);
}

void	executor(c_table **ctable)
{
	//print_struct(*ctable);
	if (*ctable == NULL)
		return ;
	if ((*ctable)->pipeout)	
		if (piperoutine(ctable))
		{
			executor(ctable);
			return ;
		}
	commands(*ctable);
	next_struct(ctable);
	executor(ctable);
}

