/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 17:02:02 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 05:44:58 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		hasnonascii(char *s)
{
	int			i;

	i = 0;
	while (s[i])
	{
		if (ft_isprint(s[i]) == 0)
		{
			return (-1);
		}
		i++;
	}
	return (0);
}

static int		quotes(char *line)
{
	int			i;
	int			nomatch;

	i = 0;
	nomatch = 0;
	while (line[i])
	{
		if (i > 0 && line[i - 1] == '\\')
			;
		else if (nomatch == 0 && line[i] == '\"')
			nomatch = 1;
		else if (nomatch == 0 && line[i] == '\'')
			nomatch = 2;
		else if (nomatch == 1 && line[i] == '\"')
			nomatch = 0;
		else if (nomatch == 2 && line[i] == '\'')
			nomatch = 0;
		i++;
	}
	return (nomatch);
}

char			*get_inputcmd(void)
{
	int			empty;
	char		*inputcmd;
	char		*extend;

	empty = 1;
	while (empty == 1)
	{
		write(1, ">> ", 3);
		get_next_line(0, &inputcmd);
		if (inputcmd != NULL && ft_strlen(inputcmd) != 0 &&
		isonlyspace(inputcmd) != 0 && hasnonascii(inputcmd) == 0)
			empty = 0;
	}
	while (quotes(inputcmd) != 0)
	{
		write(1, "dquote>> ", 9);
		get_next_line(0, &extend);
		inputcmd = ft_strjoin(inputcmd, extend);
		free(extend);
	}
	return (inputcmd);
}

t_mini			init_mini(t_mini *m)
{
	m->i = -1;
	m->cmd = ft_split_cmd(m->inputcmd, &(m->nb_cmd));
	free(m->inputcmd);
	return (*m);
}

t_mini			init_mini_args(char *line)
{
	t_mini		m;

	m.i = -1;
	m.inputcmd = ft_strdup(line);
	args_checker(m.inputcmd);
	m.cmd = ft_split_cmd(m.inputcmd, &(m.nb_cmd));
	free(m.inputcmd);
	return (m);
}
