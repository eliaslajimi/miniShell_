#include "minishell.h"

int	getfd(char *file, int mode)
{
	int fd;
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
	c_table *n;

	n = ctable;
	if (ctable->pipeout)
		while (ctable)
			if ((n = ctable) && (ctable = ctable->next))	
				free_struct(n);
	if (ctable && (ctable = ctable->next))
		free_struct(n);
	if (ctable)
		executor(ctable);
	if (!id)
		exit(0);
}

int	commands(c_table *ctable)
{
	int ret;

	/*hypethetical prototyping for the builtins
	**if (ft_strcmp(ctable->command, "grep"))
		** ret = grep(ctable->arg, ctable->flags, ctable->in, ctable->out); 
	**if (ft_strcmp(ctable->command, "echo"))
		** ret = echo(ctable->arg, ctable->flags, ctable->in, ctable->out);
	**if (ft_strcmp(ctable->command, "pwd"))
		** ret = pwd(ctable->arg, ctable->flags, ctable->in, ctable->out);
	**if (ft_strcmp(ctable->command, "echo"))
		** ret = (ctable->arg, ctable->flags, ctable->in, ctable->out); */
	next_exec(ctable);
	return (ret);
}

void	executor(c_table *ctable)
{
	if (ctable->pipeout)
		ctable->next->pipein = setpipe(&ctable->out);
	if (ctable->pipein)
		ctable->in = ctable->pipein;
	if (ctable->filein)
		ctable->in = getfd(ctable->filein, ctable->in);
	if (ctable->fileout)
		ctable->out = getfd(ctable->fileout, ctable->out);
	if (ctable->pipeout && (id = fork()))
		if(!id)
			executor(ctable->next);
	commands(ctable);
	minishell();
}

