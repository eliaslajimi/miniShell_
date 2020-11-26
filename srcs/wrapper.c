#include "minishell.h"

 int     minishell_wrapper(c_table *ctable)
 {
	char *inputcmd;

	write(1, ">> ", 3);
	inputcmd = NULL;
	get_next_line(1, &inputcmd);
	minishell_wrapper(ctable);
	return (0);
 }

