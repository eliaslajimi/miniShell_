#include "minishell.h"

int			echo(char **arg, int args_len, int in, int out)
{
	int		i;
	char	*result;
	char	*buf;
	int		ret;
	int		nflag;

	i = 1;
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
	while (i < args_len && (ft_strncmp(*arg, "-n", 2) == 0))
	{
		nflag = 1;
		arg++;
		i++;
	}
	while (i < args_len)
	{
		if (*arg)
		{
			print(*arg, out);
			arg++;
			if (*arg)
				print(" ", out);
		}
		i++;
	}
	//add_underscore(*(--arg));
	if (nflag == 0)
		print("\n", out);
	if (out > 2)
		close(out);	
	return (0);
}
