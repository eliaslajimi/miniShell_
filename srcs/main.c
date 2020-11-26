#include "minishell.h"

int	main()
{
	c_table ctable;	
	init_struct(&ctable);
	minishell_wrapper(&ctable);
	return (0);
}
