/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:06:10 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:06:11 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sighandler(int num)
{
	t_table *ctable;

	ctable = (t_table*)getstruct();
	if (num == SIGQUIT)
	{
		exitroutine(ctable);
		exit(*((int*)getglobal(STATUS)));
	}
	if (num == SIGINT)
	{
		exitroutine(ctable);
		minishell();
	}
}

int			main(int argc, char **argv, char **envp)
{
	g_env = set_env(envp);
	add_pwd();
	add_shlvl();
	add_underscore_main();
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
	{
		args(argv);
	}
	else if (argc != 1)
	{
		print("Wrong number of arguments.\n", 2);
		return (1);
	}
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	while (1)
		minishell();
	return (0);
}
