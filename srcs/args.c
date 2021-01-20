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
		parser(ctable, t.tokens);
		executor(init);
		free(t.tokens);
	}
	exitroutine(*init);
	exit(*(int*)getglobal(STATUS));
}