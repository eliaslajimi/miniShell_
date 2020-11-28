#include "minishell.h"

 int     minishell()
 {
	char	*inputcmd;
	c_table	ctable;

	init_struct(&ctable);
	write(1, ">> ", 3);
	inputcmd = NULL;
	get_next_line(1, &inputcmd);
	ctable = ctable->next;
	minishell();
	return (0);
 }
