#include "minishell.h"

char	*pwd()
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	buf = NULL;
	if ((currentdir = getcwd(buf, bufsize)) == NULL)
		pwd(bufsize);
	free(buf);
	return (currentdir);
}
