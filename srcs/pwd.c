#include "minishell.h"

int	pwd_builtin(char **args, int out)
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	if (args[1] != NULL)
	{
		print("minishell: pwd: too many arguments\n", 2);
		return(1);
	}
	bufsize = 0;
	buf = NULL;
	currentdir = getcwd(buf, bufsize);
	currentdir = ft_strjoin(currentdir, "\n");
	free(buf);
	print(currentdir, out);
	return (0);
}
