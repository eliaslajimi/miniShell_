/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:56:41 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/04 14:57:22 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	args(char **argv)
{
	t_mini	m;
	c_table	**init;
	c_table	*ctable;
	int		*status;

	status = (int*)getglobal(STATUS);
	m = init_mini_args(argv[2]);
	while (++m.i < m.nb_cmd)
	{
		if (ft_strlen(ft_strtrim(m.cmd[m.i], " \r\t\v\f")) != 0)
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
		}
	}
	exitroutine(*init);
	final_exit(*(int*)getglobal(STATUS));
}
