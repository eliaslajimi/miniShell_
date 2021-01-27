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
	//ctable->command_exists = 0;
	exitroutine(ctable);
	while (ctable)
		next_struct(&ctable);
	//minishell();
}

int			minishell()
{
	int		start = 0;
	int		end;
	char	*cmd;
	char	*inputcmd;
	char	**tokens;

	c_table **init, *ctable;
	write(1, ">> ", 3);

	get_next_line(1, &inputcmd);
	if ((inputcmd = matching_quotes(inputcmd)) == NULL)
		minishell();
	while (start < ft_strlen(inputcmd))
	{
		init = getstruct();
		*init = init_struct();
		ctable = *init;
		end = find_semic(inputcmd, start);
		cmd = ft_substr(inputcmd, start, end - start);
		start = end + 1;
		while (inputcmd[start] == ';')
			start++;
		if (!(tokens = lexer(cmd)))
			wrapper(*init);
		if (parser(ctable, tokens) < 0)
			wrapper(*init);
		else
			executor(init);
		free(tokens);
	}
	wrapper(*init);
	return (1);
}
