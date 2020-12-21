#include "minishell.h"

char *getcmd(char **cmd)
{
	int i;
	char *ret;

	i = 0;
	ret = ft_calloc(1,1);
	while(cmd[i])	
	{
		ret = ft_strjoin(ret, cmd[i]);	
		ret = ft_strjoin(ret, " ");
		i++;
	}
	return (ret);
}

int args(char **argv)
{
	char	*input;
	char	**tokens;
	c_table	*init, *ctable;

	if (ft_strcmp(argv[1], "-c"))
	{	
		input = getcmd(argv + 2);
		init_struct(&init);
		ctable = init;
		tokens = lexer(input);	
		parser(ctable, tokens);
		executor(init);	
		free(tokens);
	}
	exit(0);
}
