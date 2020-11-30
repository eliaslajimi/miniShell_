#include "minishell.h"

 int     minishell()
 {
	char	*inputcmd;
	c_table	*init, *ctable;

	ctable = init;
	init_struct(ctable);
	write(1, ">> ", 3);
	inputcmd = NULL;
	get_next_line(1, &inputcmd);
	parser(ctable, lexer(inputcmd));
	print_struct(init);
	minishell();
	return (0);
 }
