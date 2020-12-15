#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	g_env = setEnv(envp);
	char *test = env_builtin();
	printf("%s\n", test);
	minishell();
	return (0);
}
