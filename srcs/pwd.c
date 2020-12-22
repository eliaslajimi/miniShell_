#include "minishell.h"

char	*pwd(int bufsize)
{
	char	*buf;
	char	*currentdir;

	buf = NULL;
	if ((currentdir = getcwd(buf, bufsize)) == NULL)
	{
		//errno = ERANGE 		How to set this properly?
		printf("mooooore buff sizzzzze\n");
		bufsize += 100;
		pwd(bufsize);
	}
	free(buf);
	return (currentdir);
}
