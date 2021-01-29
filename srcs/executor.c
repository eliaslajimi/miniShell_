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

int	isDir(char *path)
{
	struct stat buf;
	stat(path, &buf);
	return S_ISDIR(buf.st_mode);
}

int	isFileEmpty(char *path)
{
	struct stat buf;
	stat(path, &buf);
	return (buf.st_size <= 1);
}

char	*getabspath(char *command)
{
	char	*cmd;
	char *env = cleannode(find_node("PATH"));
	char **path = ft_split(env, ':');
	struct stat buf;
	int i = 0;
	int ret = 0;
	cmd = ft_strdup(path[i]);
	cmd = ft_strjoin(cmd, "/");
	cmd = ft_strjoin(cmd, command);
	while(path[i] && ((ret = stat(cmd, &buf)) < 0))
	{
		free(cmd);
		cmd = ft_strjoin(ft_strjoin(ft_strdup(path[i++]), "/"), command);
	}
	ft_free_array(path);
	if (ret >=0)
		return (cmd);
	else
	{
		free(cmd);
		return (command);
	}
}

int	other_command(c_table *ctable)
{
	int status;
	struct stat buf;
	int ret;
	char *cmd;

	status= 0;
//This should be refactored as 'checkfileformat(char *command)'
//==============================
	if (ctable->command[0] != '.' && ctable->command[0] != '/')
		cmd = getabspath(ctable->command);
	else 
		cmd = ft_strdup(ctable->command);
	ret = stat(cmd, &buf);
	mode_t bits = buf.st_mode;	
	if (ft_strcmp(ctable->command, cmd))
	{
		if (ret < 0)
		{
			print("minishell: ",1);	//could be refactored as print_error(char *command, int error);
			print(cmd, 1);
			print(": command not found\n", 1);
			free(cmd);
			return (127);
		}
		if (isDir(cmd))
		{
			print("minishell: ", 1);
			print(cmd, 1);
			print(": is a directory\n", 1);
			free(cmd);
			return (126);
		}
		if (!(bits & S_IXUSR))// || !(bits & S_IXGRP))// && !(bits & S_IXOTH))
		{
			print("minishell: ", 1);
			print(cmd, 1);
			print(": Permission denied\n", 1);
			free(cmd);
			return (126);
		}
		status = fork_cmd(cmd, ctable->args, ctable);
		if (status == 256)
		{
			free(cmd);
			return (1);
		}
		free(cmd);
		return (status%256);
	}
	else
	{
		if (ret < 0)
		{
			print("minishell: ",1);	//could be refactored as print_error(char *command, int error);
			print(ctable->command, 1);
			print(": command not found\n", 1);
			return (127);
		}
		if (isDir(ctable->command))
		{
			print("minishell: ", 1);
			print(ctable->command, 1);
			print(": is a directory\n", 1);
			return (126);
		}
		//if (!(bits & S_IXUSR) && !(bits & S_IXGRP))// && !(bits & S_IXOTH))
		if (!(bits & S_IXUSR))// || !(bits & S_IXGRP))// && !(bits & S_IXOTH))
		{
			print("minishell: ", 1);
			print(ctable->command, 1);
			print(": Permission denied\n", 1);
			return (126);
		}
		status = fork_cmd(cmd, ctable->args, ctable);
		return (status%256);
	}
	if (cmd[ft_strlen(cmd) - 1] == '/' && isDir(ctable->command))
	{
		return (126);
	}
	if (!ft_strlen(ctable->command))
	{
		status = 0;
		return (status);
	}
	return (status);
}

void	commands(c_table *ctable)
{
	int	*status;

	status = (int*)getglobal(STATUS);
//should be refactored as formatcmd()
	if (!ft_strlen(ctable->command))
	{
		*status = other_command(ctable);
		return ;
	}
//--------------
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

