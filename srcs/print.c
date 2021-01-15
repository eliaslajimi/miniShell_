#include "minishell.h"

int print(char *s, int fd)
{
	int ret;
	
	ret = 1;
	if (s)
		ret = write(fd, s, ft_strlen(s));
	return (ret);
}
