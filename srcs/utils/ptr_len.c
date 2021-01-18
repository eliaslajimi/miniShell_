#include "../minishell.h"

int ptr_len(void **ptr)
{
	int i;

	i = 0;
	while (ptr && *ptr)
	{
		ptr++;
		i++;
	}
	return (i);
}
