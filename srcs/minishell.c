#include "minishell.h"

void	wrapper() // -_-
{
	minishell();
}

 int     minishell()
 {
	char	*inputcmd;
	char	**tokens;

	c_table	*init, *ctable;
	init = (c_table*)getglobal(STRUCT);	
	init_struct(&init);
	ctable = init;
	write(1, ">> ", 3);
	get_next_line(1, &inputcmd);
	tokens = lexer(inputcmd);	
	parser(ctable, tokens);
	ctable = init;
	executor(ctable);
	free(tokens);
 	wrapper();
	return (0);
 }
