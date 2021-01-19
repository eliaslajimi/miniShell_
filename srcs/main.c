#include "minishell.h"

void	sighandler(int num)
{
	c_table *ctable;
	
	ctable = (c_table*)getstruct();
	if (num == SIGQUIT)
	{
		exitroutine(ctable);	
		exit(*((int*)getglobal(STATUS)));
	}
	if (num == SIGINT)
	{
		exitroutine(ctable);	
		minishell();
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	add_pwd();
	add_shlvl();
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
		args(argv);
	else if (argc != 1)
	{
		print("Wrong number of arguments.\n", 2);
		return (1);
	}
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	minishell();
	return (0);
}
