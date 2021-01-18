#include "minishell.h"

void args(char **argv)
{
	int		start = 0;
	int		end;
	char	*inputcmd;
	char	*cmd;
	char	**tokens;
	c_table	**init, *ctable;

//	ctable = init;
		inputcmd = ft_strdup(argv[2]);
		while (start < ft_strlen(inputcmd))
		{
			init = getstruct();
			*init = init_struct();
			ctable = *init;
			end = find_semic(inputcmd, start);
			cmd = ft_substr(inputcmd, start, end - start);
			start = end + 1;
			if (!(tokens = lexer(cmd)))
				wrapper(*init);
			parser(ctable, tokens);
			executor(init);
			free(tokens);
		}
/*		if ((tokens = lexer(input)) != NULL)
		{
			parser(ctable, tokens);
			executor(&init);	
			free(tokens);
		}
*/
	exitroutine(*init);
	exit(*(int*)getglobal(STATUS));
}
