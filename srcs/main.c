/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:06:10 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 05:49:34 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		sighandler(int num)
{
	t_table *ctable;

	ctable = (t_table*)getstruct();
	if (num == SIGQUIT)
	{
		write(1, "core dumped\n", ft_strlen("core dumped\n"));
	}
	if (num == SIGINT)
	{
		write(1, "\n>> ", 4);
	}
}

int			main(int argc, char **argv, char **envp)
{
	t_mini	m;

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
	while (1)
	{
		signal(SIGINT, sighandler);
		signal(SIGQUIT, sighandler);
		m = prompt();
		minishell(m);
	}
	return (0);
}
