#include "minishell.h"
/*
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
*/

char	*getcmd(char *cmd)
{
	char *ret;
	ret = ft_strtrim(cmd, "\"");
//	free(cmd);
	return (ret);
}
void args(char **argv)
{
	char	*input;
	char	**tokens;
	c_table	*init, *ctable;

	if (ft_strcmp(argv[1], "-c") == 0)
	{
		input = getcmd(argv[2]);
		init_struct(&init);
		ctable = init;
		tokens = lexer(input);
		parser(ctable, tokens);
		executor(init);	
		free(tokens);
	}
	exitroutine();
}
