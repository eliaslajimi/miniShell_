#include "minishell.h"

 int     minishell()
 {
	char	*inputcmd;

	//inputcmd = NULL;
	c_table	*init, *ctable;
	init_struct(&init);
	ctable = init;
	write(1, ">> ", 3);
	get_next_line(1, &inputcmd);
	parser(ctable, lexer(inputcmd));
	print_struct(init);
	free(ctable);
	minishell();
	return (0);
 }
