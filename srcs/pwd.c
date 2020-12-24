#include "minishell.h"

int	pwd_builtin()
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	bufsize = 0;
	buf = NULL;
	currentdir = getcwd(buf, bufsize);
	free(buf);
	print(currentdir, 1);
	return (0);
}
