#include "minishell.h"

void exitroutine(c_table *ctable)
{
	(void)ctable;
	//while (ctable)
	//	next_struct(&ctable);
}

void *getglobal(int mode)
{
	static int *ret_status;
	
	if (mode == STATUS)
		return ((void*)&ret_status);
	return (NULL);
}

c_table **getstruct()
{
	static c_table *ret;
	return (&ret);
}
void	wrapper(c_table *ctable)
{
	//c_table *ctable = (c_table*)getglobal(STRUCT);
	ctable->command_exists = 0;
	exitroutine(ctable);
	while (ctable)
		next_struct(&ctable);
	minishell();
}

 int     minishell()
 {
	char	*inputcmd;
	char	**tokens;

	c_table **init, *ctable;
	init = getstruct();
	*init = init_struct();
	write(1, ">> ", 3);
	ctable = *init;
	get_next_line(1, &inputcmd);
	if (!(tokens = lexer(inputcmd)))
		wrapper(*init);
	parser(ctable, tokens);
	executor(*init);
	free(tokens);
 	wrapper(*init);
	return (0);
 }
