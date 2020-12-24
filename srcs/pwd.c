#include "minishell.h"

int	pwd_builtin(int out)
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	bufsize = 0;
	buf = NULL;
	currentdir = getcwd(buf, bufsize);
	currentdir = ft_strjoin(currentdir, "\n");
	free(buf);
	print(currentdir, out);
	return (0);
}
