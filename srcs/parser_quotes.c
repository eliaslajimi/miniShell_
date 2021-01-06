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

char	*handle_double_quote(char *token)
{
	int		i;
	int		len;
	char	*result;


	i = 1;
	while (token[i] != '$' && token[i] != '\"')
		i++;
	result = ft_strndup(token, i);
	while (token[i] == '$')
	{
		len = 0;
		i += 1;
		while (token[i] != '$' && token[i] != '\"')
		{
			len++;
			i++;
		}
		if (swap_dollar(token, i - len, len) != NULL)
			result = ft_strjoin(result, swap_dollar(token, i - len, len));
		else
			result = ft_strjoin(result, "");
		
	}
	ft_strdel(&token);
	return (ft_strtrim(result, "\""));
}

char	*handle_simple_quote(char *token)
{
	token = ft_strtrim(token, "\'");
	return (token);
}