#include "minishell.h"

char    *handlspace(char *str)
{
        int i = 0;
        int j = 0;
        char *result;

        result = malloc(sizeof(char) * (ft_strlen(str) + 1));
        while(str[i])
        {
                if (str[i] == ' ')
                {
                        result[j] = ' ';
                        j++;
                        while (str[i] == ' ')
                                i++;
                }
                result[j] = str[i];
                j++;
                i++;
        }
        result[j] = 0;
        return (result);
}

char	*swap_dollar(char *s, int i, int len)
{
	char	*tmp;
	char	*tofind;
	char	*result;

	tofind = ft_strndup(s + i, len);
	if (find_node(tofind) != NULL)
	{
		result = ft_strdup(find_node(tofind) + ft_strlen(tofind) + 1);
		tmp = result;
		result = handlspace(tmp);
		free(tmp);
		ft_strdel(&tofind);
		return (result);
	}
	free(tofind);
	return (NULL);
}