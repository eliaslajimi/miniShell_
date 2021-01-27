#include "minishell.h"

static t_arg	init_targ(char **argv)
{
	t_arg	t;
	t.start = 0;
	t.end = 0;
	t.inputcmd = ft_strdup(argv[2]);
	t.cmd = NULL;
	t.tokens = NULL;
	args_checker(t.inputcmd);
	return (t);
}

void args(char **argv)
{
	t_arg	t;
	c_table	**init;
	c_table	*ctable;
	int	*status;

	status = (int*)getglobal(STATUS);
	t = init_targ(argv);
	while (t.start < ft_strlen(t.inputcmd))
	{
		init = getstruct();
		*init = init_struct();
		ctable = *init;
		t.end = find_semic(t.inputcmd, t.start);
		t.cmd = ft_substr(t.inputcmd, t.start, t.end - t.start);
		t.start = t.end + 1;
		if (!(t.tokens = lexer(t.cmd)))
			wrapper(*init);
		if (parser(ctable, t.tokens) < 0)
			*status = 1;
		else
			executor(init);
		free(t.tokens);
	}
	exitroutine(*init);
	final_exit(*(int*)getglobal(STATUS));
}