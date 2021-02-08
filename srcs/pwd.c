/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:28:40 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 15:28:41 by cmcgahan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pwd_builtin(char **args, int out)
{
	int		bufsize;
	char	*buf;
	char	*currentdir;

	if (args[1] != NULL)
	{
		print("minishell: pwd: too many arguments\n", 2);
		return (1);
	}
	bufsize = 0;
	buf = NULL;
	currentdir = getcwd(buf, bufsize);
	currentdir = ft_strjoin(currentdir, "\n");
	print(currentdir, out);
	free(currentdir);
	return (0);
}
