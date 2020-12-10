#include "minishell.h"

int	init_struct(c_table **ctable)
{
	*ctable = malloc(sizeof(c_table));
	(*ctable)->separator = 0;
	(*ctable)->pipein = 0;
	(*ctable)->pipeout = 0;
	(*ctable)->command = "";
	(*ctable)->flags = ft_calloc(1, 1);
	(*ctable)->args = ft_calloc(1, 1); 
	(*ctable)->in = 0;
	(*ctable)->out = 1;
	(*ctable)->filein = "";
	(*ctable)->fileout = "";
	(*ctable)->next = NULL;
	return (0);
}

void next_struct(c_table **ctable)
{
	c_table *next;
	print_struct(*ctable);
	init_struct(&next);
	(*ctable)->next = next;
	(*ctable) = (*ctable)->next;
	(*ctable)->next = NULL;
}

void free_struct(c_table *ctable)
{
	free(ctable->flags);
	free(ctable->args);
	free(ctable);
}

void print_struct(c_table *ctable)
{	
	printf("\n============================================\n");
	printf("ctable: separator:	[%d]\n", ctable->separator); 
	printf("ctable: pipein:		[%d]\n", ctable->pipein); 
	printf("ctable: pipeout:	[%d]\n", ctable->pipeout); 
	printf("ctable: command:	[%s]\n", ctable->command); 
	printf("ctable: flag:		[%s]\n", ctable->flags); 
	printf("ctable: args:		[%s]\n", ctable->args); 
	printf("ctable: in:		[%d]\n", ctable->in); 
	printf("ctable: out:		[%d]\n", ctable->out); 
	printf("ctable: file in:	[%s]\n", ctable->filein); 
	printf("ctable: file out:	[%s]\n", ctable->fileout); 
	printf("============================================\n");
}
