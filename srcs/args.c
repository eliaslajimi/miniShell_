/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:56:41 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 17:10:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		isonlyspace(char *s)
{
	int	i;

	i = 0;
	while (s[i] && ft_isin(s[i], " \t\v\f\r"))
		i++;
	if (i == ft_strlen(s))
		return (0);
	return (1);
}

void	args(char **argv)
{
	t_mini	m;
	t_table	**init;
	t_table	*ctable;

	m = init_mini_args(argv[2]);
	while (++m.i < m.nb_cmd)
	{
		if (isonlyspace(m.cmd[m.i]) == 1)
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
