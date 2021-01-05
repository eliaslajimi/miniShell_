#include "minishell.h"

int echo(char **arg, char *flags, int in, int out)
{
	char *result;
	char *buf;
	int ret;
	
	buf = ft_calloc(1,1);
	result = ft_calloc(10,1);
	if (in)
		while ((ret  = read(in, buf, 10)) && ret > 0)
			result = ft_strjoin(result, buf);	
	while (*arg)	
		if ((print(*arg++, out)) && *arg)
			print(" ", out);
	if (!flags || (ft_strncmp(flags, "-n", 2)))
			print("\n", out);	
	return (1);
}
