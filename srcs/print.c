#include "minishell.h"

int print(char *s, int fd)
{
	if (s)
	{
		write(fd, s, ft_strlen(s));
	}
	return (0);
}
