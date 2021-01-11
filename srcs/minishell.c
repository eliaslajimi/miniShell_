#include "minishell.h"

void exitroutine()
{
	while (ctable)
		next_struct(&ctable);
}

void *getglobal(int mode)
{
	static int *ret_status;
	
	if (mode == STATUS)
		return ((void*)&ret_status);
	return (NULL);
}

void	wrapper(c_table *ctable)
{
	//c_table *ctable = (c_table*)getglobal(STRUCT);
	(void)ctable;
	init->command_exists = 0;
	exitroutine();
	minishell();
}

 int     minishell()
 {
	char	*inputcmd;
	char	**tokens;

	init = init_struct();
	write(1, ">> ", 3);
	ctable = init;
	get_next_line(1, &inputcmd);
	if (!(tokens = lexer(inputcmd)))
		wrapper(init);
	parser(ctable, tokens);
	executor(init);
	free(tokens);
 	wrapper(ctable);
	return (0);
 }
