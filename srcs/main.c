#include "minishell.h"


void	sighandler(int num)
{
	if (num == SIGQUIT)
	{
		exitroutine();	
		exit(*((int*)getglobal(STATUS)));
	}
	if (num == SIGINT)
	{
		exitroutine();	
		minishell();
	}
}

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	add_pwd();
	add_shlvl();
	if (argc > 1)
		args(argv);	
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	minishell();
	return (0);
}
