#include "minishell.h"

char	*swap_dollar(char *s, int i, int len)
{
	//printf("trying to swap dollar\n");
	char	*tmp;
	char	*tofind;
	char	*result;

	tofind = ft_strndup(s + i, len);
	if (find_node(tofind) != NULL)
	{
		result = ft_strdup(find_node(tofind) + ft_strlen(tofind) + 1);
		tmp = result;
		result = ft_strtrim(result, " ");	
		free(tmp);
		//printf("result is %s\n", result);
		//printf("tofind is %s\n", );
		ft_strdel(&tofind);
		return (result);
	}
	free(tofind);
	return (NULL);
}
