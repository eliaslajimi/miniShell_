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

c_table **getstruct(void)
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
	t_mini	m;
	c_table	**init;
	c_table	*ctable;

	m = init_mini();
	while (++m.i < m.nb_cmd)
	{
		if (ft_strlen(ft_strtrim(m.cmd[m.i], " \r\t\v\f")) != 0)
		{
			init = getstruct();
			*init = init_struct();
			ctable = *init;
			if (!(m.tokens = lexer(m.cmd[m.i])))
				wrapper(*init);
			if (parser(ctable, m.tokens) < 0)
				wrapper(*init);
			else
				executor(init);
			ft_free_array(m.tokens);
		}
	}
	ft_free_array(m.cmd);
	wrapper(*init);
	return (1);
}
