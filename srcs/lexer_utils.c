#include "minishell.h"

int		ft_isin(int c, char *set)
{
	while (set && *set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

int		skip_spaces(char *line)
{
	int	i;
	i = 0;
	while (ft_isin(line[i], " \t\n\r\v\f"))
		i++;
	return (i);
}

int		ft_isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int		ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
	{
		return (1);
	}
	return (0);
}


int		skip_quote(char *line, char quote, int i)
{
	int skip = i + 1;
	while (line[skip] && line[skip] != quote)
		skip++;
	if (line[skip] == quote)
		return (skip - i);
	return (0);
}
