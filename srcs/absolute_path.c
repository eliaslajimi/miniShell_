#include "minishell.h"

static int  file_exists(const char *filename)
{
    int     fd;

    if ((fd = open(filename, O_RDONLY)) > 0)
    {
        close(fd);
        return (1);
    }
    return (0);
}

static char *cmdpath(char *path, char *cmd)
{
    int     i;
    int     bin_exists;
    char    *bin;
    char    **path_split;

    i = 0;
    bin_exists = 0;
    bin = NULL;
    if (cmd[0] != '/' || ft_strncmp(cmd, "./", 2) != 0)
    {
        path_split = ft_split(path, ':');
        ft_strdel(&path);
        while (path_split[i])
        {
            if (!(bin = ft_calloc(sizeof(char), ft_strlen(path_split[i] + 1 +
            ft_strlen(cmd) + 1))))
                return (0);
            bin = ft_strjoin(bin, path_split[i]);
            bin = ft_strjoin(bin, "/");
            bin = ft_strjoin(bin, cmd);
            if (file_exists(bin) == 1)
                break;
            i++;
        }
        ft_free_array(path_split);
        if (file_exists(bin) == 0)
            return("command not found\n"); // change this
        return (bin);
    }
    else
    {
        return (cmd);
        ft_strdel(&path);        
    }
}

char    *absolute_path(char *cmd)
{
    char    *path;
    t_list  *tmp;

    tmp = g_env;
    while (tmp->next && ft_strncmp(tmp->content, "PATH", 4) == 0)
        tmp = tmp->next;
    if (!(path = ft_strdup(tmp->content)))
    {
        printf("    made up path\n");
        path = ft_strdup("/bin:/usr/local/bin:/usr/bin:/usr/local/sbin");
    }
    return (cmdpath(path, cmd));
}