#include "minishell.h"

int			echo(char **arg, int in, int out)
{
	char	*result;
	char	*buf;
	int	ret;
	int	nflag;

	ret = 0;
	nflag = 0;
	buf = malloc(10);
	result = ft_calloc(1,1);
	if (in)
	{
		if ((ret = read(in, buf, 9)) > 0)
			result = ft_strjoin(result, buf);
	}
	arg++;
	while (*arg && (ft_strncmp(*arg, "-n", 2) == 0))
	{
		nflag = 1;
		arg++;
	}
	while (arg && *arg)
	{
		if ((print(*arg, out)) && ++arg)
			print(" ", out);
	}
	if (nflag == 0)
		print("\n", out);
	if (out > 2)
		close(out);	
	return (0);
}
