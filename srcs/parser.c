/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:12:44 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:12:45 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			redirection2(t_table *ctable, char *redirec, char *file)
{
	if (ft_strcmp(redirec, "<") == 0)
	{
		ctable->filein = ft_strdup(file);
		if (ft_strcmp(ctable->filein, ""))
		{
			if (file_exists(ctable->filein) == 0)
			{
				p("minishell: ",
				ctable->filein, ": No such file or directory\n");
				return (-1);
			}
			ctable->in = open(ctable->filein, O_RDONLY);
		}
	}
	return (0);
}

int			redirection(t_table *ctable, char **token)
{
	char	*redirec;
	char	*file;

	redirec = *token;
	file = *(++token);
	if (!ft_strlen(file) || ft_isin(file[0], "|><"))
		return (p("wrong file", NULL, NULL));
	if (ft_strncmp(redirec, ">>", 2) == 0)
	{
		ctable->fileout = ft_strdup(file);
		if (ft_strcmp(ctable->fileout, "") != 0)
			ctable->out = open(ctable->fileout,
			O_CREAT | O_RDWR | O_APPEND, 0777);
	}
	else if (ft_strcmp(redirec, ">") == 0)
	{
		ctable->fileout = ft_strdup(file);
		if (ft_strcmp(ctable->fileout, "") != 0)
			ctable->out = open(ctable->fileout,
			O_CREAT | O_RDWR | O_TRUNC, 0777);
	}
	else if (redirection2(ctable, redirec, file) == -1)
		return (-1);
	return (0);
}

int			token_to_command(t_table *ctable, char **tokens)
{
	(void)ctable;
	if (is_redirec(*tokens) != 0)
	{
		if (redirection(ctable, tokens++) < 0)
			return (-1);
		return (1);
	}
	else
	{
		ctable->args = expanse_array(ctable->args,
		ctable->args_len, ft_strdup(*tokens));
		if (ctable->command_exists == 0)
			ctable->command = ft_strdup(ctable->args[0]);
		ctable->command_exists = 1;
		ctable->args_len++;
	}
	return (0);
}

void		init_tpars(t_pars *t)
{
	t->i = 0;
	t->status = (int*)getglobal(STATUS);
	t->result = 0;
}

int			parser(t_table *ctable, char **tokens)
{
	t_pars	t;

	init_tpars(&t);
	while (tokens[t.i])
	{
		if ((ctable->separator = separator(tokens[t.i])) != 0)
		{
			ctable->command_exists = 0;
			add_struct(&ctable);
		}
		if (is_pipe(tokens[t.i], ctable))
		{
			ctable->command_exists = 0;
			add_struct(&ctable);
		}
		else
		{
			if ((t.result = token_to_command(ctable, tokens + t.i)) < 0)
				return (-1);
			else if (t.result == 1)
				t.i++;
		}
		t.i++;
	}
	return (0);
}
