#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	minishell();
	return (0);
}
