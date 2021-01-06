#include "minishell.h"

int		skip_quote(char *line, char quote, int i)
{
	int skip = i + 1;
	while (line[skip] && line[skip] != quote)
		skip++;
	if (line[skip] == quote)
	{
		return (skip - i);
	}
	return (0);
}
