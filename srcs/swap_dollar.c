#include "minishell.h"

char	*swap_dollar(char *s, int i, int len)
{
	char	*tofind;
	char	*result;

	tofind = ft_strndup(s + i, len);
	if (find_node(tofind) != NULL)
	{
		result = ft_strdup(find_node(tofind) + ft_strlen(tofind) + 1);
		ft_strdel(&tofind);
		return (result);
	}
	return (NULL);
}
