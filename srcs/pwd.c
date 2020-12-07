#include "minishell.h"

void	pwd(void)
{
	char	*str;

	str = NULL;
	if (!(str = getcwd(str, 0)))
		return ; //ERROR
	printf("%s \n", str);
}
