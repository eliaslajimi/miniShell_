#include "minishell.h"

void	wrapper()
{
	minishell();
}

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
	wrapper();	//this function is solely there to mute wall/wextra/werror error.
	return (0);
 }
