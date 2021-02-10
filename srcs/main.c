/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:06:10 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/10 12:02:51 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv, char **envp);

void		sighandler(int num)
{
	t_table *ctable;
	
	ctable = (t_table*)getstruct();
	if (num == SIGQUIT)
	{
		//exitroutine(ctable);
		//exit(*((int*)getglobal(STATUS)));
		exitroutine(ctable);
		write(1, "core dumped\n", ft_strlen("core dumped\n"));
	}
	if (num == SIGINT)
	{
		exitroutine(ctable);
		write(1, "\n", 1);
		//write(1, ">> ",3);
	}
	minishell(prompt());
}

int			main(int argc, char **argv, char **envp)
{
	g_env = set_env(envp);
	add_pwd();
	add_shlvl();
	add_underscore_main();
	signal(SIGINT, sighandler);
	signal(SIGQUIT, sighandler);
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0)
	{
		args(argv);
	}
	else if (argc != 1)
	{
		print("Wrong number of arguments.\n", 2);
		return (1);
	}
//	while (1)
//	{
	minishell(prompt());
	//}
	return (0);
}
