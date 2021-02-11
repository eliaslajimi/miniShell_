/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:06:00 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/11 06:21:13 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				getfd(char *file, int mode)
{
	int			fd;

	fd = open(file, mode, 777);
	return (fd);
}

int				setpipe(int *fdin)
{
	int			fd[2];

	pipe(fd);
	if (*fdin == 1)
		*fdin = fd[1];
	return (fd[0]);
}

void			next_exec(t_table **ctable)
{
	if (!(*ctable)->id)
	{
		exit(*(int*)getglobal(STATUS));
	}
}

int				is_dir(char *path)
{
	struct stat buf;

	stat(path, &buf);
	return (S_ISDIR(buf.st_mode));
}

char			*getabspath(char *command)
{
	char		*cmd;
	char		**path;
	struct stat buf;
	int			i;
	int			ret;

	i = 0;
	ret = 0;
	path = ft_split(cleannode(find_node("PATH")), ':');
	cmd = ft_strjoin(ft_strjoin(ft_strdup(path[i]), "/"), command);
	while (path[i] && ((ret = stat(cmd, &buf)) < 0))
	{
		free(cmd);
		cmd = ft_strjoin(ft_strjoin(ft_strdup(path[i++]), "/"), command);
	}
	ft_free_array(path);
	if (ret >= 0)
		return (cmd);
	else
	{
		free(cmd);
		return (command);
	}
}
