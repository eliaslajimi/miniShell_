/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:23:31 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 05:47:24 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		*getglobal(int mode)
{
	static int *ret_status;

	if (mode == STATUS)
		return ((void*)&ret_status);
	return (NULL);
}

t_table		**getstruct(void)
{
	static t_table *ret;

	return (&ret);
}

void		wrapper(t_table *ctable)
{
	while (ctable)
		next_struct(&ctable);
}

t_mini		prompt(void)
{
	t_mini	m;

	m.inputcmd = 0;
	m.inputcmd = get_inputcmd();
	m = init_mini(&m);
	return (m);
}

int			minishell(t_mini m)
{
	t_table	**init;
	t_table	*ctable;

	while (++m.i < m.nb_cmd)
	{
		if (isonlyspace(m.cmd[m.i]) != 0)
		{
			init = getstruct();
			*init = init_struct();
			ctable = *init;
			if (!(m.tokens = lexer(m.cmd[m.i])))
				wrapper(*init);
			if (parser(ctable, m.tokens) < 0)
				wrapper(*init);
			else
				executor(init);
			ft_free_array(m.tokens);
		}
	}
	ft_free_array(m.cmd);
	wrapper(*init);
	while (m.i != -1)
		minishell(prompt());
	return (1);
}
