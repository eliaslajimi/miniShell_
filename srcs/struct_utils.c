/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:29:34 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:29:36 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		init_args(t_table **ctable)
{
	(*ctable)->args = malloc(sizeof(char*) * 1);
	(*ctable)->args[0] = 0;
}

t_table		*init_struct(void)
{
	t_table *init;

	init = (t_table*)malloc(sizeof(t_table));
	init->separator = 0;
	init->id = -1;
	init->pipein = 0;
	init->pipeout = 0;
	init->command = "";
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

void		add_struct(t_table **ctable)
{
	t_table *next;

	next = init_struct();
	(*ctable)->next = next;
	(*ctable) = (*ctable)->next;
	(*ctable)->next = NULL;
}

void		next_struct(t_table **ctable)
{
	t_table *n;

	n = *ctable;
	(*ctable) = (*ctable)->next;
	free_struct(n);
}

void		free_struct(t_table *ctable)
{
	(void)ctable;
	//free(ctable->flags);
//	if (ctable->command)
//		free(ctable->command);
//	if (ctable->args)
//		ft_free_array(ctable->args);
	free(ctable);
}

void		print_struct(t_table *ctable)
{
	int		i;

	i = 0;
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
	while (ctable->args[i])
	{
		printf("ctable: args[%d]:		[%s]\n", i, ctable->args[i]);
		i++;
	}
	printf("ctable: args_len:	[%d]\n", ctable->args_len);
	printf("ctable: in:		[%d]\n", ctable->in);
	printf("ctable: out:		[%d]\n", ctable->out);
	printf("ctable: file in:	[%s]\n", ctable->filein);
	printf("ctable: file out:	[%s]\n", ctable->fileout);
	printf("============================================\n");
}
