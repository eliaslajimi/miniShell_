#include "minishell.h"

int init_struct(c_table *ctable)
{
	ctable->echo = 0;
        ctable->cd = 0;
	ctable->pwd = 0;
        ctable->exprt = 0;
        ctable->unset = 0;
        ctable->env = 0;
        ctable->exit = 0;
        ctable->separator = 0;
	return (0);
}
