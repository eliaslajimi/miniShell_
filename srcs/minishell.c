#include "minishell.h"

 int     minishell()
 {
	char	*inputcmd;
	char	**tokens;

	c_table	*init, *ctable;
	init_struct(&init);
	ctable = init;
	write(1, ">> ", 3);
	get_next_line(1, &inputcmd);
	tokens = lexer(inputcmd);	
	parser(ctable, tokens);
	executor(init);	
	free(tokens);
	return (0);
 }
