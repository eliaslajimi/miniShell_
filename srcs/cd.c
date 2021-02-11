/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 15:06:32 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 15:34:56 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char		*getaccesserr(char *path)
{
	opendir(path);
	if (errno == EACCES)
		return (": Permission denied");
	return (": No such file or directory");
}

int			argtocmd(char *arg)
{
	int		*status;
	char	*arg2;

	if (!arg)
		return (0);
	status = (int*)getglobal(STATUS);
	if (!(arg2 = formatpath(ft_strdup(arg))))
		return (0);
	*status = applycmd(arg2);
	if (*status != 0)
	{
		print("minishell: ", 1);
		print("cd: ", 1);
		print(arg, 1);
		print(getaccesserr(arg), 1);
		print("\n", 1);
	}
	return (0);
}

char		**removeidentical(char **cmd)
{
	while (cmd && *cmd && *(cmd + 1))
	{
		if (ft_strcmp(*cmd, *(cmd + 1)))
			return (cmd);
		cmd++;
	}
	return (cmd);
}

int			cd(char **args, int in, int out)
{
	int		status;

	status = 0;
	(void)in;
	(void)out;
	args++;
	if (!ptr_len((void*)args))
		argtocmd("");
	if (*args)
	{
		if (!ft_strlen(*args))
			*args = ft_strjoin(*args, cleannode(find_node("PWD")));
		args = removeidentical(args);
		argtocmd(*args);
		args++;
	}
	return (status);
}
