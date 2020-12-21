#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	if (argc > 1)
		args(argv);	
	minishell();
	return (0);
}
