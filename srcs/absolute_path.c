#include "minishell.h"

int             file_exists(const char *path)
{
	struct stat	stats;

	if (stat(path, &stats) == 0)
	{
		if (stats.st_mode && X_OK)
			return (1);
	}
	return (0);
}

static char     *cmdpath(char *path, char *cmd)
{
    int         i;
    int         bin_exists;
    char        *bin;
    char        **path_split;
	char	    *tmp;

    i = 0;
    bin_exists = 0;
    bin = NULL;
	tmp = path;
    if (cmd[0] != '/' || ft_strncmp(cmd, "./", 2) != 0)
	{
		path = ft_strtrim(path + 5, "\'\"");	
		ft_strdel(&tmp);
		path_split = ft_split(path, ':');
        ft_strdel(&path);
        while (path_split[i])
        {
            bin = ft_strdup(path_split[i]);
            bin = ft_strjoin(bin, "/");
            bin = ft_strjoin(bin, cmd);
            if (file_exists(bin) == 1)
                break;
            i++;
        }
        ft_free_array(path_split);
        if (file_exists(bin) == 0)
        {
            free(bin);
            return(cmd);
        }
		return (bin);
    }
    else
    {
        ft_strdel(&path);
        return (cmd);
    }
}

char            *absolute_path(char *cmd)
{
    char        *path;
    t_list      *tmp;

    tmp = g_env;
    while (tmp->next && ft_strncmp(tmp->content, "PATH", 4) != 0)
        tmp = tmp->next;
    if (!(path = ft_strdup(tmp->content)))
    {
        path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/usr/local/sbin");
    }
    return (cmdpath(path, cmd));
}