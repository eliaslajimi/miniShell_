#include "minishell.h"

int			echo(char **arg, int in, int out)
{
	char	*result;
	char	*buf;
	int		ret;
	int		nflag;

	nflag = 0;
	buf = ft_calloc(1,1);
	result = ft_calloc(10,1);
	if (in)
		while ((ret  = read(in, buf, 10)) && ret > 0)
			result = ft_strjoin(result, buf);	
	arg++;
	while (*arg && (ft_strncmp(*arg, "-n", 2) == 0))
	{
		nflag = 1;
		arg++;
	}
	while (*arg)
	{
		if ((print(*arg++, out)) && *arg)
			print(" ", out);
	}
	if (nflag == 0)
		print("\n", out);
	return (0);
}
