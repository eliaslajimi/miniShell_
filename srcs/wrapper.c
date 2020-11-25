#include "minishell.h"

 int     minishell_wrapper()
 {
	char *inputcmd;

	write(1, ">> ", 3);
	inputcmd = NULL;
	get_next_line(1, &inputcmd);
	minishell_wrapper();
	return (0);
 }

