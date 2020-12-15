#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	char *test = env_builtin("");
	printf("bitebite	[%s]\n", test);
	minishell();
	return (0);
}
