/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/11 12:01:09 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 12:01:10 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*checkfileformat(char *command)
{
	char	*cmd;

	if (command[0] != '.' && command[0] != '/')
		cmd = getabspath(command);
	else
		cmd = ft_strdup(command);
	return (cmd);
}

void			init_texec(t_exec *t, t_table *ctable)
{
	t->status = 0;
	t->toreturn = 0;
	t->cmd = checkfileformat(ctable->command);
	t->ret = stat(t->cmd, &(t->buf));
	t->bits = t->buf.st_mode;
}

int				other_command3(t_table *ctable, t_exec *t)
{
	if (t->ret < 0)
	{
		p("minishell: ", ctable->command, ": command not found\n");
		return (127);
	}
	if (is_dir(ctable->command))
	{
		p("minishell: ", ctable->command, ": is a directory\n");
		return (126);
	}
	if (!(t->bits & S_IXUSR))
	{
		p("minishell: ", ctable->command, ": Permission denied\n");
		return (126);
	}
	t->status = fork_cmd(t->cmd, ctable->args, ctable);
	return (t->status % 256);
}

int				other_command2(t_table *ctable, t_exec *t)
{
	if (t->ret < 0)
	{
		p("minishell: ", t->cmd, ": command not found\n");
		t->toreturn = 127;
	}
	else if (is_dir(t->cmd))
	{
		p("minishell: ", t->cmd, ": is a directory\n");
		t->toreturn = 126;
	}
	else if (!(t->bits & S_IXUSR))
	{
		p("minishell: ", t->cmd, ": Permission denied\n");
		t->toreturn = 126;
	}
	if (t->toreturn == 0)
		t->status = fork_cmd(t->cmd, ctable->args, ctable);
	if (t->status == 256 && t->toreturn == 0)
		t->toreturn = 1;
	free(t->cmd);
	if (t->toreturn != 0)
		return (t->toreturn);
	else
		return (t->status % 256);
}

int				other_command(t_table *ctable)
{
	t_exec t;

	init_texec(&t, ctable);
	if (ft_strcmp(ctable->command, t.cmd))
	{
		return (other_command2(ctable, &t));
	}
	else
	{
		return (other_command3(ctable, &t));
	}
}
