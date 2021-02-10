/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmcgahan <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 14:32:33 by cmcgahan          #+#    #+#             */
/*   Updated: 2021/02/08 17:09:25 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				file_exists(const char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == 0)
	{
		if (stats.st_mode && X_OK)
			return (1);
	}
	return (0);
}

static char		*cmdpath2(char **path_split, char *cmd)
{
	int			i;
	char		*bin;

	i = -1;
	while (path_split[++i])
	{
		bin = ft_strjoin(ft_strjoin(ft_strdup(path_split[i]), "/"), cmd);
		if (file_exists(bin) == 1)
			break ;
		else
			free(bin);
	}
	ft_free_array(path_split);
	if (file_exists(bin) == 0)
		return (ft_strdup(cmd));
	return (bin);
}

static char		*cmdpath(char *path, char *cmd)
{
	char		**path_split;
	char		*tmp;

	tmp = path;
	if (cmd[0] != '/' || ft_strncmp(cmd, "./", 2) != 0)
	{
		path = ft_strtrim(path + 5, "\'\"");
		ft_strdel(&tmp);
		path_split = ft_split(path, ':');
		ft_strdel(&path);
		return (cmdpath2(path_split, cmd));
	}
	else
	{
		ft_strdel(&path);
		return (cmd);
	}
}

char			*absolute_path(char *cmd)
{
	char		*path;
	t_list		*tmp;

	tmp = g_env;
	while (tmp->next && ft_strncmp(tmp->content, "PATH", 4) != 0)
		tmp = tmp->next;
	if (!(path = ft_strdup(tmp->content)))
	{
		path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/usr/local/sbin");
	}
	return (cmdpath(path, cmd));
}
