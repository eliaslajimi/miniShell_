/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:01:13 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 12:01:14 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			commands2(t_table *ctable)
{
	int	*status;

	status = (int*)getglobal(STATUS);
	if (ft_strcmp(ctable->command, "exit") == 0)
		exit_builtin(ctable->args);
	else if (ft_strcmp(ctable->command, "echo") == 0)
		*status = echo(ctable->args, ctable->args_len, ctable->in, ctable->out);
	else if (ft_strcmp(ctable->command, "env") == 0)
		*status = env_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "unset") == 0)
		*status = unset_builtin_loop(ctable->args, "void");
	else if (ft_strcmp(ctable->command, "export") == 0)
		*status = export_builtin_loop(
			ctable->args, ctable->args_len, ctable->out);
	else if (ft_strcmp(ctable->command, "pwd") == 0)
		*status = pwd_builtin(ctable->args, ctable->out);
	else if (ft_strcmp(ctable->command, "cd") == 0)
		*status = cd(ctable->args, ctable->in, ctable->out);
	else
		*status = other_command(ctable);
}

void			commands(t_table *ctable)
{
	int			*status;

	status = (int*)getglobal(STATUS);
	if (!ft_strlen(ctable->command))
	{
		*status = other_command(ctable);
		return ;
	}
	commands2(ctable);
	if (ctable->pipein > 0)
	{
		close(ctable->pipein);
		close(ctable->in);
	}
	else
	{
		if (ctable->id == 0 && ctable->out > 1)
			close(ctable->out);
	}
	waitpid(ctable->id, status, 0);
	next_exec(&ctable);
}

int				pipehandler(t_table *ctable)
{
	if (ctable->pipeout)
		ctable->next->in = setpipe(&ctable->out);
	return (0);
}

int				piperoutine(t_table **ctable)
{
	int			fd[2];
	int			pid;

	pipe(fd);
	pid = fork();
	if (!pid)
	{
		close(fd[0]);
		(*ctable)->id = pid;
		(*ctable)->out = fd[1];
		return (0);
	}
	close(fd[1]);
	(*ctable)->id = pid;
	(*ctable)->next->id = (*ctable)->id;
	next_struct(ctable);
	(*ctable)->in = fd[0];
	(*ctable)->pipein = fd[1];
	return (1);
}

void			executor(t_table **ctable)
{
	if (*ctable == NULL)
		return ;
	if ((*ctable)->pipeout)
		if (piperoutine(ctable))
		{
			executor(ctable);
			return ;
		}
	commands(*ctable);
	next_struct(ctable);
	executor(ctable);
}
