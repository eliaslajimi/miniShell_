#include "minishell.h"

//void	init_args(c_table **ctable)
void	init_args(c_table **ctable)
{
	(*ctable)->args = malloc(sizeof(char*) * 1);
	(*ctable)->args[0] = 0; 
}

c_table *init_struct()
{
	c_table *init;

	init = (c_table*)malloc(sizeof(c_table));
	init->separator = 0;
	init->id = -1;
	init->pipein = 0;
	init->pipeout = 0;
	init->command = "";
	init->flags = ft_calloc(1, 1);
	init_args(&init);
	init->args_len = 0;
	init->in = 0;
	init->out = 1;
	init->filein = "";
	init->fileout = "";
	init->next = 0;
	init->command_exists = 0;
	return (init);
}

void add_struct(c_table **ctable)
{
	c_table *next;
	next = init_struct();
	(*ctable)->next = next;
	(*ctable) = (*ctable)->next;
	(*ctable)->next = NULL;
}

void next_struct(c_table **ctable)
{
	c_table *n;

	n = *ctable;
	(*ctable) = (*ctable)->next;
	free_struct(n);
}

void free_struct(c_table *ctable)
{
	free(ctable->flags);
	ft_free_array(ctable->args);
	free(ctable);
}

void print_struct(c_table *ctable)
{
	if (!ctable)
	{
	printf("ctable is NULL\n");
	return ;
}
	printf("\n============================================\n");
	printf("ctable: separator:	[%d]\n", ctable->separator); 
	printf("ctable: pipein:		[%d]\n", ctable->pipein); 
	printf("ctable: pipeout:	[%d]\n", ctable->pipeout); 
	printf("ctable: command:	[%s]\n", ctable->command); 
	printf("ctable: proc.id:	[%d]\n", ctable->id); 
	printf("ctable: flag:		[%s]\n", ctable->flags); 
	int i = 0;
	while (ctable->args[i])
	{
		printf("ctable: args[%d]:		[%s]\n",i, ctable->args[i]); 
		i++;
	}
	printf("ctable: args_len:	[%d]\n", ctable->args_len);
	printf("ctable: in:		[%d]\n", ctable->in); 
	printf("ctable: out:		[%d]\n", ctable->out); 
	printf("ctable: file in:	[%s]\n", ctable->filein); 
	printf("ctable: file out:	[%s]\n", ctable->fileout); 
	printf("============================================\n");
}
