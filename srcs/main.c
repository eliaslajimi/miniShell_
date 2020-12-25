#include "minishell.h"

void interrupt()
{
	write(1, "temp function", 10);	
}

void exitshell()
{
	exit(0);
}

void	sighandler(int num)
{
	if (num == SIGINT)
		interrupt();	
	if (num == SIGQUIT)
		exitshell();
}

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (argc > 1)
		args(argv);	
	minishell();
	return (0);
}
