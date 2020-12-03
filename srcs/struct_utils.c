#include "minishell.h"

int	init_struct(c_table **ctable)
{
	*ctable = malloc(sizeof(c_table));
	(*ctable)->separator = 0;
	(*ctable)->pipein = 0;
	(*ctable)->pipeout = 0;
	(*ctable)->command = NULL;
	(*ctable)->flags = malloc(1); 
	(*ctable)->args = malloc(1); 
	(*ctable)->in = 0;
	(*ctable)->out = 1;
	(*ctable)->flags = "";
	(*ctable)->filein = "";
	(*ctable)->fileout = "";
	(*ctable)->next = NULL;
	return (0);
}

void next_struct(c_table **ctable)
{
	c_table *next;
	
	init_struct(&next);
	(*ctable)->next = next;
	(*ctable) = (*ctable)->next;
	(*ctable)->next = NULL;
}

void print_struct(c_table *ctable)
{	
	int i;

	i = 0;
	while (ctable != NULL)
	{
		printf("\n============================================\n");
		printf("ctable%d: separator:	[%d]\n", i, ctable->separator); 
		printf("ctable%d: pipein:	[%d]\n", i, ctable->pipein); 
		printf("ctable%d: pipeout:	[%d]\n", i, ctable->pipeout); 
		printf("ctable%d: command:	[%s]\n", i, ctable->command); 
		printf("ctable%d: flag:		[%s]\n", i, ctable->flags); 
		printf("ctable%d: args:		[%s]\n", i, ctable->args); 
		printf("ctable%d: in:		[%d]\n", i, ctable->in); 
		printf("ctable%d: out:		[%d]\n", i, ctable->out); 
		printf("ctable%d: file in:	[%s]\n", i, ctable->filein); 
		printf("ctable%d: file out:	[%s]\n", i, ctable->fileout); 
		printf("============================================\n");
		ctable = ctable->next;	
		i++;
	}
}
