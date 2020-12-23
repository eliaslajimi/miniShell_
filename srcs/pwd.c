#include "minishell.h"

char	*pwd()
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	bufsize = 0;
	buf = NULL;
	if ((currentdir = getcwd(buf, bufsize)) == NULL)
		pwd(bufsize);
	free(buf);
	return (currentdir);
}
