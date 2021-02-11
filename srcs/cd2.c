/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:05:09 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 15:44:18 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*cd_print_error(char *message)
{
	print(message, 2);
	return (NULL);
}

char		*formatpath(char *path)
{
	char	*tmp;

	if (!ft_strlen(path))
		if (!(path = cleannode(find_node("HOME"))))
			return (cd_print_error("minishell: cd: HOME not set\n"));
	if (ft_strlen(path) > 1 && path[ft_strlen(path)] == '/')
		path[ft_strlen(path)] = 0;
	if (!ft_strcmp(path, "-"))
		path = cleannode(find_node("OLDPWD"));
	if ((!ft_strcmp(path, "~")) || (!ft_strncmp(path, "~/", 2)))
	{
		tmp = ++path;
		path = ft_strdup(cleannode(find_node("HOME")));
		path = ft_strjoin(ft_strjoin(path, "/"), path + 1);
		free(tmp);
	}
	if (!ft_strncmp(path, "./", 2))
	{
		tmp = path;
		path = ft_strtrim(path, "./");
		free(tmp);
	}
	return (path);
}

int			applycmd2(char *cmd, char *newcmd, int status)
{
	char	*tmp;

	tmp = cmd;
	cmd = ft_strtrim(cmd, "/");
	free(tmp);
	cmd = ft_strjoin(cmd, "/");
	if (find_node("PWD"))
	{
		if (!ft_strcmp(cleannode(find_node("PWD")), "/"))
			newcmd = ft_strjoin(ft_strdup(cleannode(find_node("PWD"))), cmd);
		else
		{
			newcmd = ft_strdup(cleannode(find_node("PWD")));
			newcmd = ft_strjoin(ft_strjoin(newcmd, "/"), cmd);
		}
	}
	else
		return (-1);
	status = chdir(newcmd);
	free(newcmd);
	free(cmd);
	return (status);
}

int			applycmd(char *cmd)
{
	int		status;
	char	*newcmd;

	newcmd = NULL;
	status = 0;
	if (!ft_strcmp(cmd, ""))
		status = chdir(cleannode(find_node("HOME")));
	if (cmd[0] == '~' || cmd[0] == '/')
		status = chdir(cmd);
	else
		status = applycmd2(cmd, newcmd, status);
	if (!status)
		add_pwd();
	return (status);
}
