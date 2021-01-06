#include "../minishell.h"

static char	*ft_strfiller(char *result, char *s1, char c)
{
	int i;

	i = 0;
	while (s1[i])
	{
		result[i] = s1[i];
		++i;
	}
	result[i] = c;
	++i;
	result[i] = '\0';
	return (result);
}

char		*ft_strjoin_char(char *s1, char c)
{
	int		i;
	char	*result;

	if (s1 == NULL)
		return (NULL);
	i = ft_strlen(s1);
	if (!(result = (char*)malloc((i + 1) * sizeof(char))))
		return (0);
	result = ft_strfiller(result, s1, c);
	free(s1);
	return (result);
}
