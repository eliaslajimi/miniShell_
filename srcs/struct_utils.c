#include "minishell.h"

int init_struct(c_table *ctable)
{
	ctable = malloc(sizeof(c_table));
	ctable->command = NULL;
	ctable->in = 0;
	ctable->out = 1;
	return (0);
}

void next_struct(c_table *ctable)
{
	write(1, "debug", 5);
	c_table *next;
	
	init_struct(ctable->next);
	ctable = ctable->next;
	ctable->next = NULL;
}

void print_struct(c_table *ctable)
{	
	int i;

	i = 0;
	while (ctable && i++)
	{
		printf("ctable%d: command: [%s]\n", i, ctable->command); 
//		while (ctable->flags)
//			printf("ctable%d: flag: [%s]\n", i, *ctable->flags++); 
		printf("ctable%d: in: [%d]\n", i, ctable->in); 
		printf("ctable%d: out: [%d]\n", i, ctable->out); 
//		while (ctable->args)
//			printf("ctable%d: args: [%s]\n", i, *ctable->args++); 
		printf("ctable%d: separator: [%d]\n", i, ctable->separator); 
		ctable = ctable->next;	
	}
}
